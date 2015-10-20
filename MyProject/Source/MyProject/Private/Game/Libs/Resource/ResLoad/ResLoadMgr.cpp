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
	m_maxParral = 8;
	m_curNum = 0;
	m_LoadData = new ResLoadData();
	//m_id2HandleDic[(int)eMRIDLoadedWebRes] = onMsgRouteResLoad;
	m_loadingDepth = 0;
}

void ResLoadMgr::postInit()
{
	// 游戏逻辑处理
	//m_resMsgRouteCB = new ResMsgRouteCB();
	//Ctx.m_instance.m_msgRouteList.addOneDisp(m_resMsgRouteCB);
}

// 重置加载设置
void ResLoadMgr::resetLoadParam(LoadParam* loadParam)
{
	loadParam->m_loadNeedCoroutine = true;
	loadParam->m_resNeedCoroutine = true;
}

ResItem* ResLoadMgr::getResource(std::string path)
{
	// 如果 path == null ，程序会宕机
	if (UtilMap::ContainsKey(m_LoadData->m_path2Res, path))
	{
		return m_LoadData->m_path2Res[path];
	}
	else
	{
		return nullptr;
	}
}

void ResLoadMgr::loadData(LoadParam* param)
{
	param->m_resPackType = eDataType;

	if (eStreamingAssets == param->m_resLoadType)
	{
		param->m_path = UtilPath::Combine(g_pLocalFileSys->getLocalReadDir(), param->m_path);
	}
	else if (ePersistentData == param->m_resLoadType)
	{
		param->m_path = UtilPath::Combine(g_pLocalFileSys->getLocalWriteDir(), param->m_path);
	}
	else if (eLoadWeb == param->m_resLoadType)
	{
		param->m_path = UtilPath::Combine(g_pCfg->m_webIP, param->m_path);
	}
	//if (!string.IsNullOrEmpty(param.m_version))
	//{
	//    param.m_path = string.Format("{0}?v={1}", param.m_path, param.m_version);
	//}
	load(param);
}

// eBundleType 打包类型资源加载
void ResLoadMgr::loadBundle(LoadParam* param)
{
	param->m_resPackType = eBundleType;
	param->m_resLoadType = g_pCfg->m_resLoadType;

	load(param);
}

// eLevelType 打包类型资源加载，都用协程加载
void ResLoadMgr::loadLevel(LoadParam* param)
{
	param->resolveLevel();

#if PKG_RES_LOAD
	param.m_resPackType = ResPackType.ePakLevelType;
	param.resolvePath();
	load(param);
#elif UnPKG_RES_LOAD
	param.m_resPackType = ResPackType.eUnPakLevelType;
	param.m_resLoadType = ResLoadType.eStreamingAssets;
	load(param);
#else
	param->m_resPackType = eLevelType;
	param->m_resLoadType = g_pCfg->m_resLoadType;
	load(param);
#endif
}

// eResourcesType 打包类型资源加载
void ResLoadMgr::loadResources(LoadParam* param)
{
	param->resolvePath();

#if PKG_RES_LOAD
	if (param.m_path.IndexOf(PakSys.PAK_EXT) != -1)     // 如果加载的是打包文件
	{
		param.m_resPackType = ResPackType.ePakType;
	}
	else        // 加载的是非打包文件
	{
		param.m_resPackType = ResPackType.eUnPakType;
	}
	load(param);
#elif UnPKG_RES_LOAD
	// 判断资源所在的目录，是在 StreamingAssets 目录还是在 persistentData 目录下，目前由于没有完成，只能从 StreamingAssets 目录下加载
	param.m_resPackType = ResPackType.eUnPakType;
	param.m_resLoadType = ResLoadType.eStreamingAssets;
	return load(param);
#else
	param->m_resPackType = eResourcesType;
	param->m_resLoadType = eLoadResource;
	load(param);
#endif
}

ResItem* ResLoadMgr::createResItem(LoadParam* param)
{
	ResItem* resItem = findResFormPool(param->m_resPackType);
	if (eLevelType == param->m_resPackType)
	{
		if (resItem == nullptr)
		{
			resItem = new LevelResItem();
		}
		((LevelResItem*)resItem)->setLevelName(param->getLvlName());
	}
	//else if (eBundleType == param->m_resPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new BundleResItem();
	//	}
	//}
	else if (eResourcesType == param->m_resPackType)
	{
		if (resItem == nullptr)
		{
			resItem = new AssetResItem();
		}

		((AssetResItem*)resItem)->setPrefabName(param->getPrefabName());
	}
	else if (eDataType == param->m_resPackType)
	{
		if (resItem == nullptr)
		{
			resItem = new BinaryResItem();
		}
	}
	//else if (eUnPakType == param.m_resPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABUnPakComFileResItem();
	//	}
	//}
	//else if (eUnPakLevelType == param->m_resPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABUnPakLevelFileResItem();
	//	}
	//	((ABUnPakLevelFileResItem*)resItem).levelName = param->getLvlName();
	//}
	//else if (ePakType == param.m_resPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABPakComFileResItem();
	//	}
	//}
	//else if (ePakLevelType == param->m_resPackType)
	//{
	//	if (resItem == nullptr)
	//	{
	//		resItem = new ABPakLevelFileResItem();
	//	}
	//	((ABPakLevelFileResItem*)resItem)->setLevelName(param->getLvlName());
	//	((ABPakLevelFileResItem*)resItem)->m_origPath = param->m_origPath;
	//}

	resItem->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	resItem->setResNeedCoroutine(param->m_resNeedCoroutine);
	resItem->setResPackType(param->m_resPackType);
	resItem->setResLoadType(param->m_resLoadType);
	resItem->setPath(param->m_path);
	resItem->setPathNoExt(param->m_pathNoExt);
	resItem->setExtName(param->getExtName());

	if (param->m_loadEventHandle != nullptr)
	{
		resItem->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->m_loadEventHandle);
	}

	return resItem;
}

LoadItem* ResLoadMgr::createLoadItem(LoadParam* param)
{
	LoadItem* loadItem = findLoadItemFormPool(param->m_resPackType);

	if (eResourcesType == param->m_resPackType)        // 默认 Bundle 中资源
	{
		if (loadItem == nullptr)
		{
			loadItem = new AssetLoadItem();
		}
	}
	//else if (eBundleType == param->m_resPackType)        // Bundle 打包模式
	//{
	//	if (loadItem == nullptr)
	//	{
	//		loadItem = new UBinaryLoadItem();
	//	}
	//}
	else if (eLevelType == param->m_resPackType)
	{
		if (loadItem == nullptr)
		{
			loadItem = new LevelLoadItem();
		}

		((LevelLoadItem*)loadItem)->setLevelName(param->getLvlName());
	}
	else if (eDataType == param->m_resPackType)
	{
		if (loadItem == nullptr)
		{
			loadItem = new UBinaryLoadItem();
		}
	}
	//else if (eUnPakType == param->m_resPackType || eUnPakLevelType == param->m_resPackType)
	//{
	//	if (loadItem == nullptr)
	//	{
	//		loadItem = new ABUnPakLoadItem();
	//	}
	//}
	//else if (ePakType == param->m_resPackType || ePakLevelType == param->m_resPackType)
	//{
	//	if (loadItem == nullptr)
	//	{
	//		loadItem = new ABPakLoadItem();
	//	}
	//}

	loadItem->setResPackType(param->m_resPackType);
	loadItem->setResLoadType(param->m_resLoadType);
	loadItem->setPath(param->m_path);
	loadItem->setPathNoExt(param->m_pathNoExt);
	loadItem->setExtName(param->getExtName());
	loadItem->setLoadNeedCoroutine(param->m_loadNeedCoroutine);
	loadItem->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(EventDispatchDelegate(this, onLoadEventHandle));

	return loadItem;
}

// 资源创建并且正在被加载
void ResLoadMgr::loadWithResCreatedAndLoad(LoadParam* param)
{
	m_LoadData->m_path2Res[param->m_path]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
	if (m_LoadData->m_path2Res[param->m_path]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
	{
		if (param->m_loadEventHandle != nullptr)
		{
			param->m_loadEventHandle(m_LoadData->m_path2Res[param->m_path]);
		}
	}
	else
	{
		if (param->m_loadEventHandle != nullptr)
		{
			m_LoadData->m_path2Res[param->m_path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->m_loadEventHandle);
		}
	}

	resetLoadParam(param);
}

void ResLoadMgr::loadWithResCreatedAndNotLoad(LoadParam* param, ResItem* resItem)
{
	m_LoadData->m_path2Res[param->m_path] = resItem;
	m_LoadData->m_path2Res[param->m_path]->getRefCountResLoadResultNotify()->getResLoadState()->setLoading();
	LoadItem* loadItem = createLoadItem(param);

	if (m_curNum < m_maxParral)
	{
		m_LoadData->m_path2LDItem[param->m_path] = loadItem;
		m_LoadData->m_path2LDItem[param->m_path]->load();
		++m_curNum;
	}
	else
	{
		UtilList::Add(m_LoadData->m_willLDItem, loadItem);
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
	++m_loadingDepth;
	if (UtilMap::ContainsKey(m_LoadData->m_path2Res, param->m_path))
	{
		loadWithResCreatedAndLoad(param);
	}
	else if (param->m_loadRes != nullptr)
	{
		loadWithResCreatedAndNotLoad(param, m_LoadData->m_path2Res[param->m_path]);
	}
	else
	{
		loadWithNotResCreatedAndNotLoad(param);
	}
	--m_loadingDepth;

	if (m_loadingDepth == 0)
	{
		unloadNoRefResFromList();
	}
}

ResItem* ResLoadMgr::getAndLoad(LoadParam* param)
{
	param->resolvePath();
	load(param);
	return getResource(param->m_path);
}

// 这个卸载有引用计数，如果有引用计数就卸载不了
void ResLoadMgr::unload(std::string path, EventDispatchDelegate loadEventHandle)
{
	if (UtilMap::ContainsKey(m_LoadData->m_path2Res, path))
	{
		m_LoadData->m_path2Res[path]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		m_LoadData->m_path2Res[path]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
		if (m_LoadData->m_path2Res[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			if (m_loadingDepth != 0)
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
	m_zeroRefResIDList.Add(path);
}

// 卸载没有引用的资源列表中的资源
void ResLoadMgr::unloadNoRefResFromList()
{
	for(std::string path : m_zeroRefResIDList.getList())
	{
		if (m_LoadData->m_path2Res[path]->getRefCountResLoadResultNotify()->getRefCount()->bNoRef())
		{
			unloadNoRef(path);
		}
	}
	m_zeroRefResIDList.Clear();
}

// 不考虑引用计数，直接卸载
void ResLoadMgr::unloadNoRef(std::string path)
{
	if (UtilMap::ContainsKey(m_LoadData->m_path2Res, path))
	{
		m_LoadData->m_path2Res[path]->unload();
		m_LoadData->m_path2Res[path]->reset();
		UtilList::Add(m_LoadData->m_noUsedResItem, m_LoadData->m_path2Res[path]);

		UtilMap::Remove(m_LoadData->m_path2Res, path);
	}
	else
	{
		g_pLogSys->log(UtilStr::Format("路径不能查找到 {0}", path));
	}
}

void ResLoadMgr::onLoadEventHandle(IDispatchObject* dispObj)
{
	LoadItem* item = (LoadItem*)dispObj;
	item->getNonRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(EventDispatchDelegate(this, onLoadEventHandle));
	if (item->getNonRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		onLoaded(item);
	}
	else if (item->getNonRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		onFailed(item);
	}

	releaseLoadItem(item);
	--m_curNum;
	loadNextItem();
}

void ResLoadMgr::onLoaded(LoadItem* item)
{
	std::string _path = item->getPath();
	if (UtilMap::ContainsKey(m_LoadData->m_path2Res, _path))
	{
		m_LoadData->m_path2Res[item->getPath()]->init(m_LoadData->m_path2LDItem[item->getPath()]);
	}
	else        // 如果资源已经没有使用的地方了
	{
		item->unload();          // 直接卸载掉
	}
}

void ResLoadMgr::onFailed(LoadItem* item)
{
	std::string path = item->getPath();
	if (UtilMap::ContainsKey(m_LoadData->m_path2Res, path))
	{
		m_LoadData->m_path2Res[path]->failed(m_LoadData->m_path2LDItem[path]);
	}
}

void ResLoadMgr::releaseLoadItem(LoadItem* item)
{
	item->reset();
	UtilList::Add(m_LoadData->m_noUsedLDItem, item);
	std::string _path = item->getPath();
	UtilMap::Remove(m_LoadData->m_path2LDItem, _path);
}

void ResLoadMgr::loadNextItem()
{
	if (m_curNum < m_maxParral)
	{
		if (UtilList::Count(m_LoadData->m_willLDItem) > 0)
		{
			std::string path = ((LoadItem*)(UtilList::At(m_LoadData->m_willLDItem, 0)))->getPath();
			m_LoadData->m_path2LDItem[path] = (LoadItem*)(UtilList::At(m_LoadData->m_willLDItem, 0));
			UtilList::RemoveAt(m_LoadData->m_willLDItem, 0);
			m_LoadData->m_path2LDItem[path]->load();

			++m_curNum;
		}
	}
}

ResItem* ResLoadMgr::findResFormPool(ResPackType type)
{
	m_retResItem = nullptr;
	for(ResItem* item : m_LoadData->m_noUsedResItem)
	{
		if (item->getResPackType() == type)
		{
			m_retResItem = item;
			UtilList::Remove(m_LoadData->m_noUsedResItem, m_retResItem);
			break;
		}
	}

	return m_retResItem;
}

LoadItem* ResLoadMgr::findLoadItemFormPool(ResPackType type)
{
	m_retLoadItem = nullptr;
	for(LoadItem* item : m_LoadData->m_noUsedLDItem)
	{
		if (item->getResPackType() == type)
		{
			m_retLoadItem = item;
			UtilList::Remove(m_LoadData->m_noUsedLDItem, m_retLoadItem);
			break;
		}
	}

	return m_retLoadItem;
}

// 资源加载完成，触发下一次加载
//void ResLoadMgr::onMsgRouteResLoad(MsgRouteBase msg)
//{
//	DataLoadItem loadItem = (msg as LoadedWebResMR).m_task as DataLoadItem;
//	loadItem.handleResult();
//}