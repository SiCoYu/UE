#include "MyProject.h"
#include "ResMgrBase.h"
#include "UtilStr.h"
#include "ResItem.h"

ResMgrBase::ResMgrBase()
{
	m_loadingDepth = 0;
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