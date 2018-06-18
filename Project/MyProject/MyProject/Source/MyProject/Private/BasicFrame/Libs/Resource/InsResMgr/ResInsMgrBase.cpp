#include "MyProject.h"
#include "ResInsMgrBase.h"
#include "UtilStr.h"
#include "ResItem.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ResInsMgrBase, GObject)

ResInsMgrBase::ResInsMgrBase()
{
	this->mLoadingDepth = 0;
}

ResInsMgrBase::~ResInsMgrBase()
{
	
}

void ResInsMgrBase::init()
{

}

void ResInsMgrBase::dispose()
{
	Iterator curIte = this->mPath2ResDic.begin();
	Iterator endIte = this->mPath2ResDic.end();

	MList<ResInsBase*> resInsList;

	while (curIte != endIte)
	{
		resInsList.add(curIte->second);
		++curIte;
	}

	this->mPath2ResDic.dispose();

	int index = 0;
	int listLen = resInsList.count();
	ResInsBase* resIns = nullptr;

	while (index < listLen)
	{
		resIns = resInsList.get(listLen);
		this->unload(resIns->getPath(), EventDispatchDelegate());

		index += 1;
	}

	resInsList.dispose();
}

ResPackType ResInsMgrBase::getResPackType()
{
	return ResPackType::eObjectType;
}

void ResInsMgrBase::loadWithResCreatedAndLoad(LoadParam* param)
{
	std::string path = param->getPath();
	ResInsBase* resIns = this->mPath2ResDic[path];

	resIns->getRefCountResLoadResultNotify()->getRefCount()->incRef();

	if (resIns->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (!param->getLoadEventHandle().empty())
		{
			param->getLoadEventHandle()(
				resIns
			);        // 直接通知上层完成加载
		}
	}
	else
	{
		if (!param->getLoadEventHandle().empty())
		{
			resIns->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->getLoadEventHandle());
		}
	}
}

void ResInsMgrBase::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (this->mPath2ResDic.containsKey(path))
	{
		ResInsBase* resIns = this->mPath2ResDic[path];

		resIns->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		resIns->getRefCountResLoadResultNotify()->getRefCount()->decRef();

		if (resIns->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
		{
			if (this->mLoadingDepth != 0)       // 如果加载深度不是 0 的，说明正在加载，不能卸载对象
			{
				this->addNoRefResId2List(path);
			}
			else
			{
				this->unloadNoRef(path);
			}
		}
	}
}

// 添加无引用资源到 List
void ResInsMgrBase::addNoRefResId2List(std::string path)
{
	this->mZeroRefResIdList.add(path);
}

// 卸载没有引用的资源列表中的资源
void ResInsMgrBase::unloadNoRefResFromList()
{
	for(std::string path : this->mZeroRefResIdList.getList())
	{
		if (this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
		{
			this->unloadNoRef(path);
		}
	}

	this->mZeroRefResIdList.clear();
}

void ResInsMgrBase::unloadNoRef(std::string path)
{
	ResInsBase* resIns = this->mPath2ResDic[path];
	resIns->unload();

	// 卸载加载的原始资源
	GResLoadMgr->unload(
		path, 
		MakeEventDispatchDelegate(
			this, 
			&ResInsMgrBase::onLoadEventHandle, 
			(uint)0
		)
	);

	this->mPath2ResDic.remove(path);
	//UtilSysLibWrap.UnloadUnusedAssets();           // 异步卸载共用资源

	MY_SAFE_DISPOSE(resIns);
}

void ResInsMgrBase::onLoadEventHandle(uint eventId, IDispatchObject* dispObj)
{
	ResItem* res = (ResItem*)dispObj;
	std::string path = res->getPath();

	if (this->mPath2ResDic.containsKey(path))
	{
		this->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getResLoadState()->copyFrom(res->getRefCountResLoadResultNotify()->getResLoadState());

		if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
		{
			this->mPath2ResDic[path]->initWithRes(res);

			if (this->mPath2ResDic[path]->getIsOrigResNeedImmeUnload())
			{
				// 卸载资源
				GResLoadMgr->unload(
					path, 
					MakeEventDispatchDelegate(
						this, 
						&ResInsMgrBase::onLoadEventHandle, 
						(uint)0
					)
				);
			}
		}
		else
		{
			this->mPath2ResDic[path]->failed(res);
			GResLoadMgr->unload(
				path, 
				MakeEventDispatchDelegate(
					this, 
					&ResInsMgrBase::onLoadEventHandle, 
					(uint)0
				)
			);
		}
	}
	else
	{
		GLogSys->log(UtilStr::Format("Path can not find {0}", path));
		GResLoadMgr->unload(
			path, 
			MakeEventDispatchDelegate(
				this, 
				&ResInsMgrBase::onLoadEventHandle, 
				(uint)0
			)
		);
	}
}

ResInsBase* ResInsMgrBase::getRes(std::string path)
{
	return this->mPath2ResDic[path];
}

// 卸载所有的资源
void ResInsMgrBase::unloadAll()
{
	// 卸载资源的时候保存的路径列表
	MList<std::string> pathList;
	for(std::pair<std::string, ResInsBase*> kv : this->mPath2ResDic.getData())
	{
		kv.second->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->clearEventHandle();
		pathList.add(kv.first);
	}

	for(std::string path : pathList.getList())
	{
		this->unload(
			path, 
			MakeEventDispatchDelegate(
				this, 
				&ResInsMgrBase::onLoadEventHandle, 
				(uint)0
			)
		);
	}

	pathList.clear();
}

MY_END_NAMESPACE