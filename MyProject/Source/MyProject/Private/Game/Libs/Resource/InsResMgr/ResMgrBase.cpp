#include "MyProject.h"
#include "ResMgrBase.h"
#include "Common.h"
#include "LoadParam.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"
#include "UtilContainers.h"
#include "UtilStr.h"
#include "InsResBase.h"
#include "ResEventDispatch.h"
#include "ResItem.h"
#include "ResLoadState.h"

ResMgrBase::ResMgrBase()
{
	m_loadingDepth = 0;
}
template<class T>
T* ResMgrBase::getAndSyncLoad(std::string path)
{
	syncLoad<T>(path);
	return (T*)getRes(path);
}

template<class T>
T* ResMgrBase::getAndAsyncLoad(std::string path, EventDispatchDelegate handle)
{
	T* ret = nullptr;
	LoadParam* param = g_pPoolSys->newObject<LoadParam>();
	LocalFileSys.modifyLoadParam(path, param);
	param.m_loadNeedCoroutine = true;
	param.m_resNeedCoroutine = true;
	param.m_loadEventHandle = handle;
	ret = getAndLoad<T>(param);
	Ctx.m_instance.m_poolSys.deleteObj(param);

	return ret;
}

template<class T>
T* ResMgrBase::getAndLoad(LoadParam* param)
{
	load<T>(param);
	return (T*)getRes(param.m_path);
}

// 同步加载，立马加载完成，并且返回加载的资源， syncLoad 同步加载资源不能喝异步加载资源的接口同时去加载一个资源，如果异步加载一个资源，这个时候资源还没有加载完成，然后又同步加载一个资源，这个时候获取的资源是没有加载完成的，由于同步加载资源没有回调，因此即使同步加载的资源加载完成，也不可能获取加载完成事件
template<class T>
void ResMgrBase::syncLoad(std::string path)
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
T* ResMgrBase::createResItem(LoadParam* param)
{
	T* ret = new T();
	ret->getRefCountResLoadResultNotify()->getRefCount().incRef();
	ret.m_path = param->m_path;

	ret.refCountResLoadResultNotify.loadResEventDispatch.addEventHandle(param.m_loadEventHandle);

	return ret;
}

void ResMgrBase::loadWithResCreatedAndLoad(LoadParam* param)
{
	m_path2ResDic[param->m_path]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	if (m_path2ResDic[param->m_path]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (!param->m_loadEventHandle.empty())
		{
			param->m_loadEventHandle(m_path2ResDic[param->m_path]);        // 直接通知上层完成加载
		}
	}
	else
	{
		if (!param->m_loadEventHandle.empty())
		{
			m_path2ResDic[param->m_path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->m_loadEventHandle);
		}
	}
}

template<class T>
void ResMgrBase::loadWithResCreatedAndNotLoad(LoadParam* param, T* resItem)
{
	m_path2ResDic[param->m_path] = resItem;
	m_path2ResDic[param->m_path].getRefCountResLoadResultNotify()->getResLoadState()->setLoading();
	param->m_loadEventHandle = onLoadEventHandle;
	g_pResLoadMgr->loadResources(param);
}

template<class T>
void ResMgrBase::loadWithNotResCreatedAndNotLoad(LoadParam* param)
{
	T* resItem = createResItem<T>(param);
	loadWithResCreatedAndNotLoad<T>(param, resItem);
}

template<class T>
void ResMgrBase::load(LoadParam* param)
{
	++m_loadingDepth;
	if (UtilMap::ContainsKey(m_path2ResDic, param->m_path))
	{
		loadWithResCreatedAndLoad(param);
	}
	else if (param.m_loadInsRes != nullptr)
	{
		loadWithResCreatedAndNotLoad<T>(param, (T*)(param->m_loadInsRes));
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

void ResMgrBase::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (UtilMap::ContainsKey(m_path2ResDic, path))
	{
		m_path2ResDic[path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		m_path2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
		if (m_path2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
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
void ResMgrBase::addNoRefResID2List(std::string path)
{
	m_zeroRefResIDList.Add(path);
}

// 卸载没有引用的资源列表中的资源
void ResMgrBase::unloadNoRefResFromList()
{
	for(std::string path : m_zeroRefResIDList.getList())
	{
		if (m_path2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			unloadNoRef(path);
		}
	}
	m_zeroRefResIDList.Clear();
}

void ResMgrBase::unloadNoRef(std::string path)
{
	m_path2ResDic[path]->unload();
	// 卸载加载的原始资源
	g_pResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
	UtilMap::Remove(m_path2ResDic, path);
	//UtilApi.UnloadUnusedAssets();           // 异步卸载共用资源
}

void ResMgrBase::onLoadEventHandle(IDispatchObject* dispObj)
{
	ResItem* res = (ResItem*)dispObj;
	std::string path = res->getPath();

	if (UtilMap::ContainsKey(m_path2ResDic, path))
	{
		m_path2ResDic[path]->getRefCountResLoadResultNotify()->getResLoadState()->copyFrom(res->getRefCountResLoadResultNotify()->getResLoadState());
		if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
		{
			m_path2ResDic[path]->init(res);
			if (m_path2ResDic[path]->getIsOrigResNeedImmeUnload())
			{
				// 卸载资源
				g_pResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
			}
		}
		else
		{
			m_path2ResDic[path]->failed(res);
			g_pResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
		}
	}
	else
	{
		g_pLogSys->log(UtilStr::Format("路径不能查找到 {0}", path));
		g_pResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
	}
}

InsResBase* ResMgrBase::getRes(std::string path)
{
	return m_path2ResDic[path];
}

// 卸载所有的资源
void ResMgrBase::unloadAll()
{
	// 卸载资源的时候保存的路径列表
	MList<std::string> pathList;
	for(std::pair<std::string, InsResBase*> kv : m_path2ResDic)
	{
		kv.second->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->clearEventHandle();
		pathList.Add(kv.first);
	}

	for(std::string path : pathList.getList())
	{
		unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
	}

	pathList.Clear();
}