#include "MyProject.h"
#include "ResMgrBase.h"

ResMgrBase::ResMgrBase()
{
	m_loadingDepth = 0;
}
template<class T>
T ResMgrBase::getAndSyncLoad<T>(string path)
{
	syncLoad<T>(path);
	return getRes(path) as T;
}

template<class T>
T ResMgrBase::getAndAsyncLoad<T>(string path, Action<IDispatchObject> handle)
{
	T ret = null;
	LoadParam param = Ctx.m_instance.m_poolSys.newObject<LoadParam>();
	LocalFileSys.modifyLoadParam(path, param);
	param.m_loadNeedCoroutine = true;
	param.m_resNeedCoroutine = true;
	param.m_loadEventHandle = handle;
	ret = getAndLoad<T>(param);
	Ctx.m_instance.m_poolSys.deleteObj(param);

	return ret;
}

template<class T>
T ResMgrBase::getAndLoad<T>(LoadParam param)
{
	load<T>(param);
	return getRes(param.m_path) as T;
}

// 同步加载，立马加载完成，并且返回加载的资源， syncLoad 同步加载资源不能喝异步加载资源的接口同时去加载一个资源，如果异步加载一个资源，这个时候资源还没有加载完成，然后又同步加载一个资源，这个时候获取的资源是没有加载完成的，由于同步加载资源没有回调，因此即使同步加载的资源加载完成，也不可能获取加载完成事件
template<class T>
void ResMgrBase::syncLoad<T>(string path)
{
	LoadParam param;
	param = Ctx.m_instance.m_poolSys.newObject<LoadParam>();
	param.m_path = path;
	// param.m_loadEventHandle = onLoadEventHandle;        // 这个地方是同步加载，因此不需要回调，如果写了，就会形成死循环， InsResBase 中的 init 又会调用 onLoadEventHandle 这个函数，这个函数是外部回调的函数，由于同步加载，没有回调，因此不要设置这个 param.m_loadEventHandle = onLoadEventHandle ，内部会自动调用
	param.m_loadNeedCoroutine = false;
	param.m_resNeedCoroutine = false;
	load<T>(param);
	Ctx.m_instance.m_poolSys.deleteObj(param);
}

template<class T>
T ResMgrBase::createResItem<T>(LoadParam param)
{
	T ret = new T();
	ret.refCountResLoadResultNotify.refCount.incRef();
	ret.m_path = param.m_path;

	ret.refCountResLoadResultNotify.loadResEventDispatch.addEventHandle(param.m_loadEventHandle);

	return ret;
}

void ResMgrBase::loadWithResCreatedAndLoad(LoadParam param)
{
	m_path2ResDic[param.m_path].refCountResLoadResultNotify.refCount.incRef();
	if (m_path2ResDic[param.m_path].refCountResLoadResultNotify.resLoadState.hasLoaded())
	{
		if (param.m_loadEventHandle != null)
		{
			param.m_loadEventHandle(m_path2ResDic[param.m_path]);        // 直接通知上层完成加载
		}
	}
	else
	{
		if (param.m_loadEventHandle != null)
		{
			m_path2ResDic[param.m_path].refCountResLoadResultNotify.loadResEventDispatch.addEventHandle(param.m_loadEventHandle);
		}
	}
}

template<class T>
void ResMgrBase::loadWithResCreatedAndNotLoad<T>(LoadParam param, T resItem)
{
	m_path2ResDic[param.m_path] = resItem;
	m_path2ResDic[param.m_path].refCountResLoadResultNotify.resLoadState.setLoading();
	param.m_loadEventHandle = onLoadEventHandle;
	Ctx.m_instance.m_resLoadMgr.loadResources(param);
}

template<class T>
void ResMgrBase::loadWithNotResCreatedAndNotLoad<T>(LoadParam param)
{
	T resItem = createResItem<T>(param);
	loadWithResCreatedAndNotLoad<T>(param, resItem);
}

template<class T>
void ResMgrBase::load<T>(LoadParam param)
{
	++m_loadingDepth;
	if (m_path2ResDic.ContainsKey(param.m_path))
	{
		loadWithResCreatedAndLoad(param);
	}
	else if (param.m_loadInsRes != null)
	{
		loadWithResCreatedAndNotLoad<T>(param, param.m_loadInsRes as T);
	}
	else
	{
		loadWithNotResCreatedAndNotLoad<T>(param);
	}
	--m_loadingDepth;

	if (m_loadingDepth == 0)
	{
		unloadNoRefResFromList();
	}
}

void ResMgrBase::unload(string path, Action<IDispatchObject> loadEventHandle)
{
	if (m_path2ResDic.ContainsKey(path))
	{
		m_path2ResDic[path].refCountResLoadResultNotify.loadResEventDispatch.removeEventHandle(loadEventHandle);
		m_path2ResDic[path].refCountResLoadResultNotify.refCount.decRef();
		if (m_path2ResDic[path].refCountResLoadResultNotify.refCount.bNoRef())
		{
			if (m_loadingDepth != 0)       // 如果加载深度不是 0 的，说明正在加载，不能卸载对象
			{
				addNoRefResID2List(path);
			}
			else
			{
				unloadNoRef(path);
			}
		}
	}
}

// 添加无引用资源到 List
void ResMgrBase::addNoRefResID2List(string path)
{
	m_zeroRefResIDList.Add(path);
}

// 卸载没有引用的资源列表中的资源
void ResMgrBase::unloadNoRefResFromList()
{
	foreach(string path in m_zeroRefResIDList)
	{
		if (m_path2ResDic[path].refCountResLoadResultNotify.refCount.bNoRef())
		{
			unloadNoRef(path);
		}
	}
	m_zeroRefResIDList.Clear();
}

void ResMgrBase::unloadNoRef(string path)
{
	m_path2ResDic[path].unload();
	// 卸载加载的原始资源
	Ctx.m_instance.m_resLoadMgr.unload(path, onLoadEventHandle);
	m_path2ResDic.Remove(path);
	//UtilApi.UnloadUnusedAssets();           // 异步卸载共用资源
}

void ResMgrBase::onLoadEventHandle(IDispatchObject dispObj)
{
	ResItem res = dispObj as ResItem;
	string path = res.GetPath();

	if (m_path2ResDic.ContainsKey(path))
	{
		m_path2ResDic[path].refCountResLoadResultNotify.resLoadState.copyFrom(res.refCountResLoadResultNotify.resLoadState);
		if (res.refCountResLoadResultNotify.resLoadState.hasSuccessLoaded())
		{
			m_path2ResDic[path].init(res);
			if (m_path2ResDic[path].bOrigResNeedImmeUnload)
			{
				// 卸载资源
				Ctx.m_instance.m_resLoadMgr.unload(path, onLoadEventHandle);
			}
		}
		else
		{
			m_path2ResDic[path].failed(res);
			Ctx.m_instance.m_resLoadMgr.unload(path, onLoadEventHandle);
		}
	}
	else
	{
		Ctx.m_instance.m_logSys.log(string.Format("路径不能查找到 {0}", path));
		Ctx.m_instance.m_resLoadMgr.unload(path, onLoadEventHandle);
	}
}

object ResMgrBase::getRes(string path)
{
	return m_path2ResDic[path];
}

// 卸载所有的资源
void ResMgrBase::unloadAll()
{
	// 卸载资源的时候保存的路径列表
	List<string> pathList = new List<string>();
	foreach(KeyValuePair<string, InsResBase> kv in m_path2ResDic)
	{
		kv.Value.refCountResLoadResultNotify.loadResEventDispatch.clearEventHandle();
		pathList.Add(kv.Key);
	}

	foreach(string path in pathList)
	{
		unload(path, onLoadEventHandle);
	}

	pathList.Clear();
}