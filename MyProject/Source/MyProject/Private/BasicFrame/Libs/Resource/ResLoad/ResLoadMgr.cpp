#include "MyProject.h"
#include "ResLoadMgr.h"
#include "ResLoadData.h"
#include "UtilContainers.h"
#include "LoadParam.h"
#include "UtilStr.h"
#include "Common.h"
#include "LoadItem.h"
#include "ResItem.h"
#include "NonRefCountResLoadResultNotify.h"
#include "ResEventDispatch.h"
#include "ResLoadState.h"
#include "EventDispatchDelegate.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"
#include "ResLoadResultNotify.h"
#include "AssetLoadItem.h"
#include "BinaryLoadItem.h"
#include "LevelLoadItem.h"
#include "AssetResItem.h"
#include "BinaryResItem.h"
#include "LevelResItem.h"
#include "UtilPath.h"

ResLoadMgr::ResLoadMgr()
{
	mMaxParral = 8;
	mCurNum = 0;
	mLoadData = new ResLoadData();
	//mId2HandleDic[(int)eMRIDLoadedWebRes] = onMsgRouteResLoad;
	mLoadingDepth = 0;
}

void ResLoadMgr::init()
{
	// 游戏逻辑处理
	//mResMsgRouteCB = new ResMsgRouteCB();
	//Ctx.m_instance.m_msgRouteList.addOneDisp(mResMsgRouteCB);
}

void ResLoadMgr::dispose()
{

}

// 重置加载设置
void ResLoadMgr::resetLoadParam(LoadParam* loadParam)
{
	loadParam->mIsLoadNeedCoroutine = true;
	loadParam->mIsResNeedCoroutine = true;
}

void ResLoadMgr::loadAsset(LoadParam* param)
{

}

ResItem* ResLoadMgr::getResource(std::string path)
{
	// 如果 path == null ，程序会宕机
	if (UtilMap::ContainsKey(mLoadData->mPath2Res, path))
	{
		return mLoadData->mPath2Res[path];
	}
	else
	{
		return nullptr;
	}
}

LoadItem* ResLoadMgr::getLoadItem(std::string path)
{
	if (UtilMap::ContainsKey(mLoadData->mPath2LDItem, path))
	{
		return mLoadData->mPath2LDItem[path];
	}
	else
	{
		return nullptr;
	}
}

void ResLoadMgr::loadData(LoadParam* param)
{
	// 链接不过
	param->mResPackType = eDataType;

	if (eStreamingAssets == param->mResLoadType)
	{
		param->mPath = UtilPath::Combine(GLocalFileSys->getLocalReadDir(), param->mPath);
	}
	else if (ePersistentData == param->mResLoadType)
	{
		param->mPath = UtilPath::Combine(GLocalFileSys->getLocalWriteDir(), param->mPath);
	}
	else if (eLoadWeb == param->mResLoadType)
	{
		param->mPath = UtilPath::Combine(GCfg->mWebIP, param->mPath);
	}
	//if (!string.IsNullOrEmpty(param.mVersion))
	//{
	//    param.mPath = string.Format("{0}?v={1}", param.mPath, param.mVersion);
	//}
	load(param);
}

// eBundleType 打包类型资源加载
void ResLoadMgr::loadBundle(LoadParam* param)
{
	param->mResPackType = eBundleType;
	param->mResLoadType = GCfg->mResLoadType;

	load(param);
}

// eLevelType 打包类型资源加载，都用协程加载
void ResLoadMgr::loadLevel(LoadParam* param)
{
	param->resolveLevel();

#if PKG_RES_LOAD
	param.mResPackType = ResPackType.ePakLevelType;
	param.resolvePath();
	load(param);
#elif UnPKG_RES_LOAD
	param.mResPackType = ResPackType.eUnPakLevelType;
	param.mResLoadType = ResLoadType.eStreamingAssets;
	load(param);
#else
	param->mResPackType = eLevelType;
	param->mResLoadType = GCfg->mResLoadType;
	load(param);
#endif
}

// eResourcesType 打包类型资源加载
void ResLoadMgr::loadResources(LoadParam* param)
{
	param->resolvePath();

#if PKG_RES_LOAD
	if (param.mPath.IndexOf(PakSys.PAK_EXT) != -1)     // 如果加载的是打包文件
	{
		param.mResPackType = ResPackType.ePakType;
	}
	else        // 加载的是非打包文件
	{
		param.mResPackType = ResPackType.eUnPakType;
	}
	load(param);
#elif UnPKG_RES_LOAD
	// 判断资源所在的目录，是在 StreamingAssets 目录还是在 persistentData 目录下，目前由于没有完成，只能从 StreamingAssets 目录下加载
	param.mResPackType = ResPackType.eUnPakType;
	param.mResLoadType = ResLoadType.eStreamingAssets;
	return load(param);
#else
	param->mResPackType = eResourcesType;
	param->mResLoadType = eLoadResource;
	load(param);
#endif
}

ResItem* ResLoadMgr::createResItem(LoadParam* param)
{
	ResItem* resItem = findResFormPool(param->mResPackType);

	if (ePakClass == param->mResPackType)
	{
		if (nullptr == resItem)
		{
			resItem = new LevelResItem();
		}
	}
	else if (eLevelType == param->mResPackType)
	{
		if (nullptr == resItem)
		{
			resItem = new LevelResItem();
		}
		((LevelResItem*)resItem)->setLevelName(param->getLvlName());
	}
	//else if (eBundleType == param->mResPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new BundleResItem();
	//	}
	//}
	else if (eResourcesType == param->mResPackType)
	{
		if (nullptr == resItem)
		{
			resItem = new AssetResItem();
		}

		((AssetResItem*)resItem)->setPrefabName(param->getPrefabName());
	}
	else if (eDataType == param->mResPackType)
	{
		if (nullptr == resItem)
		{
			resItem = new BinaryResItem();
		}
	}
	//else if (eUnPakType == param.mResPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABUnPakComFileResItem();
	//	}
	//}
	//else if (eUnPakLevelType == param->mResPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABUnPakLevelFileResItem();
	//	}
	//	((ABUnPakLevelFileResItem*)resItem).levelName = param->getLvlName();
	//}
	//else if (ePakType == param.mResPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABPakComFileResItem();
	//	}
	//}
	//else if (ePakLevelType == param->mResPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABPakLevelFileResItem();
	//	}
	//	((ABPakLevelFileResItem*)resItem)->setLevelName(param->getLvlName());
	//	((ABPakLevelFileResItem*)resItem)->mOrigPath = param->mOrigPath;
	//}

	resItem->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	resItem->setResNeedCoroutine(param->mIsResNeedCoroutine);
	resItem->setResPackType(param->mResPackType);
	resItem->setResLoadType(param->mResLoadType);
	resItem->setPath(param->mPath);
	resItem->setPathNoExt(param->mPathNoExt);
	resItem->setExtName(param->getExtName());

	if (nullptr != param->mLoadEventHandle)
	{
		resItem->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);
	}

	return resItem;
}

LoadItem* ResLoadMgr::createLoadItem(LoadParam* param)
{
	LoadItem* loadItem = findLoadItemFormPool(param->mResPackType);

	if (eResourcesType == param->mResPackType)        // 默认 Bundle 中资源
	{
		if (loadItem == nullptr)
		{
			loadItem = new AssetLoadItem();
		}
	}
	//else if (eBundleType == param->mResPackType)        // Bundle 打包模式
	//{
	//	if (loadItem == nullptr)
	//	{
	//		loadItem = new UBinaryLoadItem();
	//	}
	//}
	else if (eLevelType == param->mResPackType)
	{
		if (loadItem == nullptr)
		{
			loadItem = new LevelLoadItem();
		}

		((LevelLoadItem*)loadItem)->setLevelName(param->getLvlName());
	}
	else if (eDataType == param->mResPackType)
	{
		if (loadItem == nullptr)
		{
			loadItem = new UBinaryLoadItem();
		}
	}
	//else if (eUnPakType == param->mResPackType || eUnPakLevelType == param->mResPackType)
	//{
	//	if (loadItem == nullptr)
	//	{
	//		loadItem = new ABUnPakLoadItem();
	//	}
	//}
	//else if (ePakType == param->mResPackType || ePakLevelType == param->mResPackType)
	//{
	//	if (loadItem == nullptr)
	//	{
	//		loadItem = new ABPakLoadItem();
	//	}
	//}

	loadItem->setResPackType(param->mResPackType);
	loadItem->setResLoadType(param->mResLoadType);
	loadItem->setPath(param->mPath);
	loadItem->setPathNoExt(param->mPathNoExt);
	loadItem->setExtName(param->getExtName());
	loadItem->setLoadNeedCoroutine(param->mIsLoadNeedCoroutine);
	loadItem->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(EventDispatchDelegate(this, &ResLoadMgr::onLoadEventHandle));

	return loadItem;
}

// 资源创建并且正在被加载
void ResLoadMgr::loadWithResCreatedAndLoad(LoadParam* param)
{
	mLoadData->mPath2Res[param->mPath]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	if (mLoadData->mPath2Res[param->mPath]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (param->mLoadEventHandle != nullptr)
		{
			param->mLoadEventHandle(mLoadData->mPath2Res[param->mPath]);
		}
	}
	else
	{
		if (param->mLoadEventHandle != nullptr)
		{
			mLoadData->mPath2Res[param->mPath]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);
		}
	}

	resetLoadParam(param);
}

void ResLoadMgr::loadWithResCreatedAndNotLoad(LoadParam* param, ResItem* resItem)
{
	mLoadData->mPath2Res[param->mPath] = resItem;
	mLoadData->mPath2Res[param->mPath]->getRefCountResLoadResultNotify()->getResLoadState()->setLoading();

	LoadItem* loadItem = getLoadItem(param->mPath);

	if (nullptr == loadItem)
	{
		loadItem = createLoadItem(param);

		if (mCurNum < mMaxParral)
		{
			mLoadData->mPath2LDItem[param->mPath] = loadItem;
			mLoadData->mPath2LDItem[param->mPath]->load();
			++mCurNum;
		}
		else
		{
			UtilList::Add(mLoadData->mWillLDItem, loadItem);
		}
	}
	else
	{
		loadItem->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(EventDispatchDelegate(this, &ResLoadMgr::onLoadEventHandle));
	}

	resetLoadParam(param);
}

void ResLoadMgr::loadWithNotResCreatedAndNotLoad(LoadParam* param)
{
	ResItem* resItem = createResItem(param);
	loadWithResCreatedAndNotLoad(param, resItem);
}

// 通用类型，需要自己设置很多参数
void ResLoadMgr::load(LoadParam* param)
{
	++mLoadingDepth;
	if (UtilMap::ContainsKey(mLoadData->mPath2Res, param->mPath))
	{
		loadWithResCreatedAndLoad(param);
	}
	else if (param->mLoadRes != nullptr)
	{
		loadWithResCreatedAndNotLoad(param, mLoadData->mPath2Res[param->mPath]);
	}
	else
	{
		loadWithNotResCreatedAndNotLoad(param);
	}
	--mLoadingDepth;

	if (mLoadingDepth == 0)
	{
		unloadNoRefResFromList();
	}
}

ResItem* ResLoadMgr::getAndLoad(LoadParam* param)
{
	param->resolvePath();
	load(param);
	return getResource(param->mPath);
}

// 这个卸载有引用计数，如果有引用计数就卸载不了
void ResLoadMgr::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (UtilMap::ContainsKey(mLoadData->mPath2Res, path))
	{
		mLoadData->mPath2Res[path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		mLoadData->mPath2Res[path]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
		if (mLoadData->mPath2Res[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			if (mLoadingDepth != 0)
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
void ResLoadMgr::addNoRefResID2List(std::string path)
{
	mZeroRefResIDList.Add(path);
}

// 卸载没有引用的资源列表中的资源
void ResLoadMgr::unloadNoRefResFromList()
{
	for(std::string path : mZeroRefResIDList.getList())
	{
		if (mLoadData->mPath2Res[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			unloadNoRef(path);
		}
	}
	mZeroRefResIDList.Clear();
}

// 不考虑引用计数，直接卸载
void ResLoadMgr::unloadNoRef(std::string path)
{
	if (UtilMap::ContainsKey(mLoadData->mPath2Res, path))
	{
		mLoadData->mPath2Res[path]->unload();
		mLoadData->mPath2Res[path]->reset();
		UtilList::Add(mLoadData->mNoUsedResItem, mLoadData->mPath2Res[path]);

		UtilMap::Remove(mLoadData->mPath2Res, path);
	}
	else
	{
		GLogSys->log(UtilStr::Format("路径不能查找到 {0}", path));
	}
}

void ResLoadMgr::onLoadEventHandle(IDispatchObject* dispObj)
{
	LoadItem* item = (LoadItem*)dispObj;
	item->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(EventDispatchDelegate(this, &ResLoadMgr::onLoadEventHandle));
	if (item->getNonRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		onLoaded(item);
	}
	else if (item->getNonRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		onFailed(item);
	}

	releaseLoadItem(item);
	--mCurNum;
	loadNextItem();
}

void ResLoadMgr::onLoaded(LoadItem* item)
{
	std::string _path = item->getPath();
	if (UtilMap::ContainsKey(mLoadData->mPath2Res, _path))
	{
		mLoadData->mPath2Res[item->getPath()]->init(mLoadData->mPath2LDItem[item->getPath()]);
	}
	else        // 如果资源已经没有使用的地方了
	{
		item->unload();          // 直接卸载掉
	}
}

void ResLoadMgr::onFailed(LoadItem* item)
{
	std::string path = item->getPath();
	if (UtilMap::ContainsKey(mLoadData->mPath2Res, path))
	{
		mLoadData->mPath2Res[path]->failed(mLoadData->mPath2LDItem[path]);
	}
}

void ResLoadMgr::releaseLoadItem(LoadItem* item)
{
	item->reset();
	UtilList::Add(mLoadData->mNoUsedLDItem, item);
	std::string _path = item->getPath();
	UtilMap::Remove(mLoadData->mPath2LDItem, _path);
}

void ResLoadMgr::loadNextItem()
{
	if (mCurNum < mMaxParral)
	{
		if (UtilList::Count(mLoadData->mWillLDItem) > 0)
		{
			std::string path = ((LoadItem*)(UtilList::At(mLoadData->mWillLDItem, 0)))->getPath();
			mLoadData->mPath2LDItem[path] = (LoadItem*)(UtilList::At(mLoadData->mWillLDItem, 0));
			UtilList::RemoveAt(mLoadData->mWillLDItem, 0);
			mLoadData->mPath2LDItem[path]->load();

			++mCurNum;
		}
	}
}

ResItem* ResLoadMgr::findResFormPool(ResPackType type)
{
	mRetResItem = nullptr;
	for(ResItem* item : mLoadData->mNoUsedResItem)
	{
		if (item->getResPackType() == type)
		{
			mRetResItem = item;
			UtilList::Remove(mLoadData->mNoUsedResItem, mRetResItem);
			break;
		}
	}

	return mRetResItem;
}

LoadItem* ResLoadMgr::findLoadItemFormPool(ResPackType type)
{
	mRetLoadItem = nullptr;
	for(LoadItem* item : mLoadData->mNoUsedLDItem)
	{
		if (item->getResPackType() == type)
		{
			mRetLoadItem = item;
			UtilList::Remove(mLoadData->mNoUsedLDItem, mRetLoadItem);
			break;
		}
	}

	return mRetLoadItem;
}

// 资源加载完成，触发下一次加载
//void ResLoadMgr::onMsgRouteResLoad(MsgRouteBase msg)
//{
//	DataLoadItem loadItem = (msg as LoadedWebResMR).m_task as DataLoadItem;
//	loadItem.handleResult();
//}