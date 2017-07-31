#include "MyProject.h"
#include "InsResMgrBase.h"
#include "UtilStr.h"
#include "ResItem.h"

InsResMgrBase::InsResMgrBase()
{
	this->mLoadingDepth = 0;
}

void InsResMgrBase::init()
{

}

void InsResMgrBase::dispose()
{

}

void InsResMgrBase::loadWithResCreatedAndLoad(LoadParam* param)
{
	this->mPath2ResDic[param->getPath()]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	if (this->mPath2ResDic[param->getPath()]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (!param->getLoadEventHandle().empty())
		{
			param->getLoadEventHandle()(this->mPath2ResDic[param->getPath()]);        // 直接通知上层完成加载
		}
	}
	else
	{
		if (!param->getLoadEventHandle().empty())
		{
			this->mPath2ResDic[param->getPath()]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->getLoadEventHandle());
		}
	}
}

void InsResMgrBase::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (UtilMap::ContainsKey(this->mPath2ResDic, path))
	{
		this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
		if (this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
		{
			if (this->mLoadingDepth != 0)       // 如果加载深度不是 0 的，说明正在加载，不能卸载对象
			{
				this->addNoRefResID2List(path);
			}
			else
			{
				this->unloadNoRef(path);
			}
		}
	}
}

// 添加无引用资源到 List
void InsResMgrBase::addNoRefResID2List(std::string path)
{
	this->mZeroRefResIDList.Add(path);
}

// 卸载没有引用的资源列表中的资源
void InsResMgrBase::unloadNoRefResFromList()
{
	for(std::string path : this->mZeroRefResIDList.getList())
	{
		if (this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
		{
			this->unloadNoRef(path);
		}
	}
	this->mZeroRefResIDList.Clear();
}

void InsResMgrBase::unloadNoRef(std::string path)
{
	this->mPath2ResDic[path]->unload();
	// 卸载加载的原始资源
	GResLoadMgr->unload(path, EventDispatchDelegate(this, &InsResMgrBase::onLoadEventHandle));
	UtilMap::Remove(this->mPath2ResDic, path);
	//UtilApi.UnloadUnusedAssets();           // 异步卸载共用资源
}

void InsResMgrBase::onLoadEventHandle(IDispatchObject* dispObj)
{
	ResItem* res = (ResItem*)dispObj;
	std::string path = res->getPath();

	if (UtilMap::ContainsKey(this->mPath2ResDic, path))
	{
		this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getResLoadState()->copyFrom(res->getRefCountResLoadResultNotify()->getResLoadState());
		if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
		{
			this->mPath2ResDic[path]->init(res);
			if (this->mPath2ResDic[path]->getIsOrigResNeedImmeUnload())
			{
				// 卸载资源
				GResLoadMgr->unload(path, EventDispatchDelegate(this, &InsResMgrBase::onLoadEventHandle));
			}
		}
		else
		{
			this->mPath2ResDic[path]->failed(res);
			GResLoadMgr->unload(path, EventDispatchDelegate(this, &InsResMgrBase::onLoadEventHandle));
		}
	}
	else
	{
		GLogSys->log(UtilStr::Format("Path can not find {0}", path));
		GResLoadMgr->unload(path, EventDispatchDelegate(this, &InsResMgrBase::onLoadEventHandle));
	}
}

InsResBase* InsResMgrBase::getRes(std::string path)
{
	return this->mPath2ResDic[path];
}

// 卸载所有的资源
void InsResMgrBase::unloadAll()
{
	// 卸载资源的时候保存的路径列表
	MList<std::string> pathList;
	for(std::pair<std::string, InsResBase*> kv : this->mPath2ResDic)
	{
		kv.second->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->clearEventHandle();
		pathList.Add(kv.first);
	}

	for(std::string path : pathList.getList())
	{
		this->unload(path, EventDispatchDelegate(this, &InsResMgrBase::onLoadEventHandle));
	}

	pathList.Clear();
}