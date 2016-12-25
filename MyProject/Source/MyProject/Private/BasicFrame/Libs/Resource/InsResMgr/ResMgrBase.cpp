#include "MyProject.h"
#include "ResMgrBase.h"
#include "UtilStr.h"
#include "ResItem.h"

ResMgrBase::ResMgrBase()
{
	mLoadingDepth = 0;
}

void ResMgrBase::init()
{

}

void ResMgrBase::dispose()
{

}

void ResMgrBase::loadWithResCreatedAndLoad(LoadParam* param)
{
	mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	if (mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (!param->mLoadEventHandle.empty())
		{
			param->mLoadEventHandle(mPath2ResDic[param->mPath]);        // 直接通知上层完成加载
		}
	}
	else
	{
		if (!param->mLoadEventHandle.empty())
		{
			mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);
		}
	}
}

void ResMgrBase::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (UtilMap::ContainsKey(mPath2ResDic, path))
	{
		mPath2ResDic[path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
		if (mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			if (mLoadingDepth != 0)       // 如果加载深度不是 0 的，说明正在加载，不能卸载对象
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
	mZeroRefResIDList.Add(path);
}

// 卸载没有引用的资源列表中的资源
void ResMgrBase::unloadNoRefResFromList()
{
	for(std::string path : mZeroRefResIDList.getList())
	{
		if (mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			unloadNoRef(path);
		}
	}
	mZeroRefResIDList.Clear();
}

void ResMgrBase::unloadNoRef(std::string path)
{
	mPath2ResDic[path]->unload();
	// 卸载加载的原始资源
	GResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
	UtilMap::Remove(mPath2ResDic, path);
	//UtilApi.UnloadUnusedAssets();           // 异步卸载共用资源
}

void ResMgrBase::onLoadEventHandle(IDispatchObject* dispObj)
{
	ResItem* res = (ResItem*)dispObj;
	std::string path = res->getPath();

	if (UtilMap::ContainsKey(mPath2ResDic, path))
	{
		mPath2ResDic[path]->getRefCountResLoadResultNotify()->getResLoadState()->copyFrom(res->getRefCountResLoadResultNotify()->getResLoadState());
		if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
		{
			mPath2ResDic[path]->init(res);
			if (mPath2ResDic[path]->getIsOrigResNeedImmeUnload())
			{
				// 卸载资源
				GResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
			}
		}
		else
		{
			mPath2ResDic[path]->failed(res);
			GResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
		}
	}
	else
	{
		GLogSys->log(UtilStr::Format("Path can not find {0}", path));
		GResLoadMgr->unload(path, EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle));
	}
}

InsResBase* ResMgrBase::getRes(std::string path)
{
	return mPath2ResDic[path];
}

// 卸载所有的资源
void ResMgrBase::unloadAll()
{
	// 卸载资源的时候保存的路径列表
	MList<std::string> pathList;
	for(std::pair<std::string, InsResBase*> kv : mPath2ResDic)
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