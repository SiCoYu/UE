#include "MyProject.h"
#include "ResLoadMgr.h"
#include "ResLoadData.h"
#include "UtilContainers.h"
#include "LoadParam.h"
#include "UtilStr.h"
#include "Prequisites.h"
#include "LoadItem.h"
#include "ResItem.h"
#include "NonRefCountResLoadResultNotify.h"
#include "ResEventDispatch.h"
#include "ResLoadState.h"
#include "EventDispatchDelegate.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"
#include "ResLoadResultNotify.h"
#include "ClassAssetLoadItem.h"
#include "ObjectAssetLoadItem.h"
#include "BinaryLoadItem.h"
#include "LevelLoadItem.h"
#include "ClassAssetResItem.h"
#include "ObjectAssetResItem.h"
#include "BinaryResItem.h"
#include "LevelResItem.h"
#include "UtilPath.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

ResLoadMgr::ResLoadMgr()
{
	this->mMaxParral = 8;
	this->mCurNum = 0;
	this->mLoadData = MY_NEW ResLoadData();
	//mId2HandleDic[(int)eMRIDLoadedWebRes] = onMsgRouteResLoad;
	this->mLoadingDepth = 0;
}

ResLoadMgr::~ResLoadMgr()
{
	
}

void ResLoadMgr::init()
{
	// 游戏逻辑处理
	//mResMsgRouteCB = new ResMsgRouteCB();
	//Ctx.m_instance.m_msgRouteList.addOneNotify(mResMsgRouteCB);
}

void ResLoadMgr::dispose()
{
	// 卸载加载的资源
	typename ResLoadData::ResItemIterator curIte = this->mLoadData->mPath2ResDic.begin();
	typename ResLoadData::ResItemIterator endIte = this->mLoadData->mPath2ResDic.end();

	MList<ResItem*> resList;

	while (curIte != endIte)
	{
		resList.add(curIte->second);
		++curIte;
	}

	this->mLoadData->mPath2ResDic.dispose();

	int index = 0;
	int listLen = resList.count();
	ResItem* res = nullptr;

	while (index < listLen)
	{
		res = resList.get(index);
		this->unload(res->getPath(), EventDispatchDelegate());

		index += 1;
	}

	resList.dispose();

	// 卸载缓存的资源
	index = 0;
	listLen = this->mLoadData->mNoUsedResItemList.count();
	res = nullptr;

	while (index < listLen)
	{
		res = this->mLoadData->mNoUsedResItemList.get(index);
		res->unload();
		MY_SAFE_DISPOSE(res);

		index += 1;
	}

	this->mLoadData->mNoUsedResItemList.dispose();

	// 加载项
	LoadItem* loadItem = nullptr;

	// 卸载加载项
	typename ResLoadData::LoadItemIterator curLoadItemIte = this->mLoadData->mPath2LoadItemDic.begin();
	typename ResLoadData::LoadItemIterator endLoadItemIte = this->mLoadData->mPath2LoadItemDic.end();

	while (curIte != endIte)
	{
		loadItem = curLoadItemIte->second;
		loadItem->unload();
		MY_SAFE_DISPOSE(loadItem);
		++curIte;
	}

	this->mLoadData->mPath2LoadItemDic.dispose();

	index = 0;
	listLen = this->mLoadData->mWillLoadItemList.count();
	loadItem = nullptr;

	while (index < listLen)
	{
		loadItem = this->mLoadData->mWillLoadItemList.get(index);
		loadItem->unload();
		MY_SAFE_DISPOSE(loadItem);

		index += 1;
	}

	this->mLoadData->mWillLoadItemList.dispose();

	index = 0;
	listLen = this->mLoadData->mNoUsedLoadItemList.count();
	loadItem = nullptr;

	while (index < listLen)
	{
		loadItem = this->mLoadData->mNoUsedLoadItemList.get(index);
		loadItem->unload();
		MY_SAFE_DISPOSE(loadItem);

		index += 1;
	}

	this->mLoadData->mNoUsedLoadItemList.dispose();

	MY_SAFE_DISPOSE(this->mLoadData);
}

// 重置加载设置
void ResLoadMgr::resetLoadParam(LoadParam* loadParam)
{
	loadParam->setIsLoadNeedCoroutine(true);
	loadParam->setIsResNeedCoroutine(true);
}

void ResLoadMgr::loadAsset(LoadParam* param)
{
	this->load(param);
}

ResItem* ResLoadMgr::getResource(std::string path)
{
	// 如果 path == nullptr ，程序会宕机
	if (this->mLoadData->mPath2ResDic.containsKey(path))
	{
		return this->mLoadData->mPath2ResDic[path];
	}
	else
	{
		return nullptr;
	}
}

LoadItem* ResLoadMgr::getLoadItem(std::string path)
{
	if (this->mLoadData->mPath2LoadItemDic.containsKey(path))
	{
		return this->mLoadData->mPath2LoadItemDic[path];
	}
	else
	{
		return nullptr;
	}
}

void ResLoadMgr::loadData(LoadParam* param)
{
	// 链接不过
	param->setResPackType(ResPackType::eDataType);

	if (ResLoadType::eLoadStreamingAssets == param->getResLoadType())
	{
		param->setPath(UtilPath::Combine(GFileSys->getLocalReadDir(), param->getPath()));
	}
	else if (ResLoadType::eLoadPersistentData == param->getResLoadType())
	{
		param->setPath(UtilPath::Combine(GFileSys->getLocalWriteDir(), param->getPath()));
	}
	else if (ResLoadType::eLoadWeb == param->getResLoadType())
	{
		param->setPath(UtilPath::Combine(GCfg->mWebIP, param->getPath()));
	}
	//if (!string.IsNullOrEmpty(param.mVersion))
	//{
	//    param.mPath = string.Format("{0}?v={1}", param.mPath, param.mVersion);
	//}
	this->load(param);
}

// eBundleType 打包类型资源加载
void ResLoadMgr::loadBundle(LoadParam* param)
{
	param->setResPackType(ResPackType::eBundleType);
	param->setResLoadType(GCfg->mResLoadType);

	this->load(param);
}

// eLevelType 打包类型资源加载，都用协程加载
void ResLoadMgr::loadLevel(LoadParam* param)
{
	param->resolveLevel();

// warning C4668: 'PKG_RES_LOAD' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#ifdef PKG_RES_LOAD
	param.mResPackType = ResPackType.ePakLevelType;
	param.resolvePath();
	load(param);
#elif defined UnPKG_RES_LOAD
	param.mResPackType = ResPackType.eUnPakLevelType;
	param.mResLoadType = ResLoadType::eStreamingAssets;
	load(param);
#else
	param->setResPackType(ResPackType::eLevelType);
	param->setResLoadType(GCfg->mResLoadType);
	load(param);
#endif
}

// eResourcesType 打包类型资源加载
void ResLoadMgr::loadResources(LoadParam* param)
{
	param->resolvePath();

#ifdef PKG_RES_LOAD
	if (param.mPath.IndexOf(PakSys.PAK_EXT) != -1)     // 如果加载的是打包文件
	{
		param.mResPackType = ResPackType.ePakType;
	}
	else        // 加载的是非打包文件
	{
		param.mResPackType = ResPackType.eUnPakType;
	}
	load(param);
#elif defined UnPKG_RES_LOAD
	// 判断资源所在的目录，是在 StreamingAssets 目录还是在 persistentData 目录下，目前由于没有完成，只能从 StreamingAssets 目录下加载
	param.mResPackType = ResPackType.eUnPakType;
	param.mResLoadType = ResLoadType::eStreamingAssets;
	return load(param);
#else
	param->setResPackType(ResPackType::eResourcesType);
	param->setResLoadType(ResLoadType::eLoadResource);
	load(param);
#endif
}

ResItem* ResLoadMgr::createResItem(LoadParam* param)
{
	ResItem* resItem = this->findResFormPool(param->getResPackType());

	if (ResPackType::eClassType == param->getResPackType())
	{
		if (nullptr == resItem)
		{
			resItem = MY_NEW ClassAssetResItem();
		}

		((ClassAssetResItem*)resItem)->setPrefabName(param->getPrefabName());
	}
	else if (ResPackType::eObjectType == param->getResPackType())
	{
		if (nullptr == resItem)
		{
			resItem = MY_NEW ObjectAssetResItem();
		}

		((ObjectAssetResItem*)resItem)->setPrefabName(param->getPrefabName());
	}
	//else if (eResourcesType == param->mResPackType)
	//{
	//	if (nullptr == resItem)
	//	{
	//		resItem = new AssetResItem();
	//	}

	//	((AssetResItem*)resItem)->setPrefabName(param->getPrefabName());
	//}
	//else if (eBundleType == param->mResPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new BundleResItem();
	//	}
	//}
	else if (ResPackType::eLevelType == param->getResPackType())
	{
		if (nullptr == resItem)
		{
			resItem = MY_NEW LevelResItem();
		}

		((LevelResItem*)resItem)->setLevelName(param->getLvlName());
	}
	else if (ResPackType::eDataType == param->getResPackType())
	{
		if (nullptr == resItem)
		{
			resItem = MY_NEW BinaryResItem();
		}
	}

	resItem->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	resItem->setLoadParam(param);

	if (!param->getLoadEventHandle().empty())
	{
		resItem->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->getLoadEventHandle());
	}

	return resItem;
}

LoadItem* ResLoadMgr::createLoadItem(LoadParam* param)
{
	LoadItem* loadItem = this->findLoadItemFormPool(param->getResPackType());

	if (ResPackType::eClassType == param->getResPackType())
	{
		if (nullptr == loadItem)
		{
			loadItem = MY_NEW ClassAssetLoadItem();
		}
	}
	else if (ResPackType::eObjectType == param->getResPackType())
	{
		if (nullptr == loadItem)
		{
			loadItem = MY_NEW ObjectAssetLoadItem();
		}
	}
	//if (eResourcesType == param->mResPackType)        // 默认 Bundle 中资源
	//{
	//	if (nullptr == loadItem)
	//	{
	//		loadItem = new AssetLoadItem();
	//	}
	//}
	//else if (eBundleType == param->mResPackType)        // Bundle 打包模式
	//{
	//	if (nullptr == loadItem)
	//	{
	//		loadItem = new UBinaryLoadItem();
	//	}
	//}
	else if (ResPackType::eLevelType == param->getResPackType())
	{
		if (nullptr == loadItem)
		{
			loadItem = MY_NEW LevelLoadItem();
		}

		((LevelLoadItem*)loadItem)->setLevelName(param->getLvlName());
	}
	else if (ResPackType::eDataType == param->getResPackType())
	{
		if (nullptr == loadItem)
		{
			loadItem = MY_NEW UBinaryLoadItem();
		}
	}

	loadItem->setLoadParam(param);
	loadItem->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&ResLoadMgr::onLoadEventHandle, 
			(uint)0
		)
	);

	return loadItem;
}

// 资源创建并且正在被加载
void ResLoadMgr::loadWithResCreatedAndLoad(LoadParam* param)
{
	this->mLoadData->mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getRefCount()->incRef();

	if (this->mLoadData->mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (!param->getLoadEventHandle().empty())
		{
			param->getLoadEventHandle()(
				this->mLoadData->mPath2ResDic[param->mPath]
			);
		}
	}
	else
	{
		if (!param->getLoadEventHandle().empty())
		{
			this->mLoadData->mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->getLoadEventHandle());
		}
	}

	this->resetLoadParam(param);
}

void ResLoadMgr::loadWithResCreatedAndNotLoad(LoadParam* param, ResItem* resItem)
{
	this->mLoadData->mPath2ResDic[param->mPath] = resItem;
	this->mLoadData->mPath2ResDic[param->mPath]->getRefCountResLoadResultNotify()->getResLoadState()->setLoading();

	LoadItem* loadItem = this->getLoadItem(param->mPath);

	if (nullptr == loadItem)
	{
		loadItem = this->createLoadItem(param);

		if (this->mCurNum < this->mMaxParral)
		{
			this->mLoadData->mPath2LoadItemDic[param->mPath] = loadItem;
			loadItem->load();
			this->mCurNum += 1;
		}
		else
		{
			this->mLoadData->mWillLoadItemList.add(loadItem);
		}
	}
	else
	{
		loadItem->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(
			MakeEventDispatchDelegate(
				this, 
				&ResLoadMgr::onLoadEventHandle, 
				(uint)0
			)
		);
	}

	this->resetLoadParam(param);
}

void ResLoadMgr::loadWithNotResCreatedAndNotLoad(LoadParam* param)
{
	ResItem* resItem = this->createResItem(param);
	this->loadWithResCreatedAndNotLoad(param, resItem);
}

// 通用类型，需要自己设置很多参数
void ResLoadMgr::load(LoadParam* param)
{
	this->mLoadingDepth += 1;

	if (this->mLoadData->mPath2ResDic.containsKey(param->mPath))
	{
		this->loadWithResCreatedAndLoad(param);
	}
	else if (param->getLoadRes() != nullptr)
	{
		this->loadWithResCreatedAndNotLoad(param, this->mLoadData->mPath2ResDic[param->mPath]);
	}
	else
	{
		this->loadWithNotResCreatedAndNotLoad(param);
	}

	this->mLoadingDepth -= 1;

	if (this->mLoadingDepth == 0)
	{
		this->unloadNoRefResFromList();
	}
}

ResItem* ResLoadMgr::getAndLoad(LoadParam* param)
{
	param->resolvePath();
	this->load(param);
	return this->getResource(param->mPath);
}

// 这个卸载有引用计数，如果有引用计数就卸载不了
void ResLoadMgr::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (this->mLoadData->mPath2ResDic.containsKey(path))
	{
		this->mLoadData->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		this->mLoadData->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
		if (this->mLoadData->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
		{
			if (this->mLoadingDepth != 0)
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
void ResLoadMgr::addNoRefResId2List(std::string path)
{
	this->mZeroRefResIdList.add(path);
}

// 卸载没有引用的资源列表中的资源
void ResLoadMgr::unloadNoRefResFromList()
{
	for(std::string path : this->mZeroRefResIdList.getList())
	{
		if (this->mLoadData->mPath2ResDic[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
		{
			this->unloadNoRef(path);
		}
	}
	this->mZeroRefResIdList.clear();
}

// 不考虑引用计数，直接卸载
void ResLoadMgr::unloadNoRef(std::string path)
{
	if (this->mLoadData->mPath2ResDic.containsKey(path))
	{
		ResItem* res = nullptr;
		res = this->mLoadData->mPath2ResDic[path];
		res->unload();
		res->reset();

		this->mLoadData->mNoUsedResItemList.add(res);
		this->mLoadData->mPath2ResDic.remove(path);
	}
	else
	{
		GLogSys->log(UtilStr::Format("路径不能查找到 {0}", path));
	}
}

void ResLoadMgr::onLoadEventHandle(uint eventId, IDispatchObject* dispObj)
{
	LoadItem* item = (LoadItem*)dispObj;

	item->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&ResLoadMgr::onLoadEventHandle, 
			(uint)0
		)
	);

	if (item->getNonRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onLoaded(item);
	}
	else if (item->getNonRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		this->onFailed(item);
	}

	this->releaseLoadItem(item);
	--this->mCurNum;
	this->loadNextItem();
}

void ResLoadMgr::onLoaded(LoadItem* item)
{
	std::string path = item->getPath();

	if (this->mLoadData->mPath2ResDic.containsKey(path))
	{
		this->mLoadData->mPath2ResDic.value(path)->initWithLoad(this->mLoadData->mPath2LoadItemDic.value(path));
	}
	else        // 如果资源已经没有使用的地方了
	{
		item->unload();          // 直接卸载掉
	}
}

void ResLoadMgr::onFailed(LoadItem* item)
{
	std::string path = item->getPath();

	if (this->mLoadData->mPath2ResDic.containsKey(path))
	{
		this->mLoadData->mPath2ResDic[path]->failed(mLoadData->mPath2LoadItemDic[path]);
	}
}

void ResLoadMgr::releaseLoadItem(LoadItem* item)
{
	item->reset();
	this->mLoadData->mNoUsedLoadItemList.add(item);
	std::string _path = item->getPath();
	this->mLoadData->mPath2LoadItemDic.remove(_path);
}

void ResLoadMgr::loadNextItem()
{
	if (this->mCurNum < this->mMaxParral)
	{
		if (this->mLoadData->mWillLoadItemList.count() > 0)
		{
			std::string path = ((LoadItem*)(this->mLoadData->mWillLoadItemList.get(0)))->getPath();
			mLoadData->mPath2LoadItemDic[path] = (LoadItem*)(this->mLoadData->mWillLoadItemList.get(0));

			this->mLoadData->mWillLoadItemList.removeAt(0);
			this->mLoadData->mPath2LoadItemDic[path]->load();

			++this->mCurNum;
		}
	}
}

ResItem* ResLoadMgr::findResFormPool(ResPackType type)
{
	this->mRetResItem = nullptr;
	for(ResItem* item : this->mLoadData->mNoUsedResItemList.getList())
	{
		if (item->getResPackType() == type)
		{
			this->mRetResItem = item;
			this->mLoadData->mNoUsedResItemList.remove(this->mRetResItem);
			break;
		}
	}

	return this->mRetResItem;
}

LoadItem* ResLoadMgr::findLoadItemFormPool(ResPackType type)
{
	this->mRetLoadItem = nullptr;

	for(LoadItem* item : this->mLoadData->mNoUsedLoadItemList.getList())
	{
		if (item->getResPackType() == type)
		{
			this->mRetLoadItem = item;
			this->mLoadData->mNoUsedLoadItemList.remove(this->mRetLoadItem);
			break;
		}
	}

	return this->mRetLoadItem;
}

// 资源加载完成，触发下一次加载
//void ResLoadMgr::onMsgRouteResLoad(MsgRouteBase msg)
//{
//	DataLoadItem loadItem = (msg as LoadedWebResMR).m_task as DataLoadItem;
//	loadItem.handleResult();
//}

MY_END_NAMESPACE