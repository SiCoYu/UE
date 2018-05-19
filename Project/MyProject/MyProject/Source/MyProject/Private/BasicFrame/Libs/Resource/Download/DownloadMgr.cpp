#include "MyProject.h"
#include "DownloadMgr.h"
#include "DownloadData.h"
#include "DownloadParam.h"
#include "DownloadItem.h"
#include "ResLoadState.h"
#include "HttpWebDownloadItem.h"
#include "RefCount.h"

DownloadMgr::DownloadMgr()
{
    mMaxParral = 8;
    mCurNum = 0;
    mLoadData = new DownloadData();
    mLoadingDepth = 0;

    //this.addMsgRouteHandle(MsgRouteId.eMRIDLoadedWebRes, onMsgRouteResLoad);
}

void DownloadMgr::init()
{
    // 游戏逻辑处理
    //mResMsgRouteCB = new ResMsgRouteCB();
    //Ctx.mInstance.mMsgRouteNotify.addOneNotify(mResMsgRouteCB);
}

void DownloadMgr::dispose()
{

}

void DownloadMgr::resetLoadParam(DownloadParam* loadParam)
{
    loadParam->reset();
}

// 是否有正在加载的 DownloadItem
bool DownloadMgr::hasDownloadItem(std::string resUniqueId)
{
	DownloadItem* loadItemValue = nullptr;

	for (DownloadData::KVPairs kvValue : mLoadData->mPath2LDItem)
    {
		loadItemValue = kvValue.second;

        if (loadItemValue->getResUniqueId() == resUniqueId)
        {
            return true;
        }
    }

    for (DownloadItem* loadItem : mLoadData->mWillLDItem)
    {
        if (loadItem->getResUniqueId() == resUniqueId)
        {
            return true;
        }
    }

    return false;
}

// 重置加载设置
void DownloadMgr::resetDownloadParam(DownloadParam* loadParam)
{
    loadParam->reset();
}

// 资源是否已经加载，包括成功和失败
bool DownloadMgr::isDownloaded(std::string path)
{
    DownloadItem* downloadItem = this->getDownloadItem(path);
    if (downloadItem == nullptr)
    {
        return false;
    }
    else if (downloadItem->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded() ||
        downloadItem->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
    {
        return true;
    }

    return false;
}

bool DownloadMgr::isSuccessDownLoaded(std::string resUniqueId)
{
    DownloadItem* downloadItem = this->getDownloadItem(resUniqueId);
    if (downloadItem == nullptr)
    {
        return false;
    }
    else if (downloadItem->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
    {
        return true;
    }

    return false;
}

DownloadItem* DownloadMgr::getDownloadItem(std::string resUniqueId)
{
	DownloadItem* loadItemValue = nullptr;

    for (DownloadData::KVPairs kvValue : mLoadData->mPath2LDItem)
    {
		loadItemValue = kvValue.second;

        if (loadItemValue->getResUniqueId() == resUniqueId)
        {
            return loadItemValue;
        }
    }

    for (DownloadItem* loadItem : mLoadData->mWillLDItem)
    {
        if (loadItem->getResUniqueId() == resUniqueId)
        {
            return loadItem;
        }
    }

    return nullptr;
}

DownloadItem* DownloadMgr::createDownloadItem(DownloadParam* param)
{
    DownloadItem* loadItem = findDownloadItemFormPool();
    if (loadItem == nullptr)
    {
        if (param->mDownloadType == eHttpWeb)
        {
            loadItem = new HttpWebDownloadItem();
        }
    }
    loadItem->setLoadParam(param);
    loadItem->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&DownloadMgr::onLoadEventHandle
		)
	);
    loadItem->getAllLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);

    return loadItem;
}

void DownloadMgr::downloadWithDownloading(DownloadParam* param)
{
    mLoadData->mPath2LDItem[param->mResUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
    if (mLoadData->mPath2LDItem[param->mResUniqueId]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
    {
        if (param->mLoadEventHandle != nullptr)
        {
            param->mLoadEventHandle(mLoadData->mPath2LDItem[param->mResUniqueId]);
        }
    }
    else
    {
        if (param->mLoadEventHandle != nullptr)
        {
            mLoadData->mPath2LDItem[param->mResUniqueId]->getAllLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);
        }
    }

    resetLoadParam(param);
}

void DownloadMgr::downloadWithNotDownload(DownloadParam* param)
{
    if (!hasDownloadItem(param->mResUniqueId))
    {
        DownloadItem* loadItem = createDownloadItem(param);

        if (mCurNum < mMaxParral)
        {
            // 先增加，否则退出的时候可能是先减 1 ，导致越界出现很大的值
            ++mCurNum;
            mLoadData->mPath2LDItem[param->mResUniqueId] = loadItem;
            mLoadData->mPath2LDItem[param->mResUniqueId]->load();
        }
        else
        {
            UtilList::Add(mLoadData->mWillLDItem, loadItem);
        }
    }

    resetLoadParam(param);
}

// 通用类型，需要自己设置很多参数
void DownloadMgr::download(DownloadParam* param)
{
    ++mLoadingDepth;
    if (UtilMap::ContainsKey(mLoadData->mPath2LDItem, param->mResUniqueId))
    {
        downloadWithDownloading(param);
    }
    else
    {
        downloadWithNotDownload(param);
    }
    --mLoadingDepth;

    if (mLoadingDepth == 0)
    {
        unloadNoRefResFromList();
    }
}

DownloadItem* DownloadMgr::getAndDownload(DownloadParam* param)
{
    //param.resolvePath();
	download(param);
    return getDownloadItem(param->mResUniqueId);
}

// 这个卸载有引用计数，如果有引用计数就卸载不了
void DownloadMgr::undownload(std::string resUniqueId, EventDispatchDelegate loadEventHandle)
{
    if (UtilMap::ContainsKey(mLoadData->mPath2LDItem, resUniqueId))
    {
        // 移除事件监听器，因为很有可能移除的时候，资源还没加载完成，这个时候事件监听器中的处理函数列表还没有清理
        mLoadData->mPath2LDItem[resUniqueId]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
        mLoadData->mPath2LDItem[resUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
        if (mLoadData->mPath2LDItem[resUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
        {
            if (mLoadingDepth != 0)
            {
                addNoRefResID2List(resUniqueId);
            }
            else
            {
                unloadNoRef(resUniqueId);
            }
        }
    }
}

// 卸载所有的资源
void DownloadMgr::unloadAll()
{
    MList<std::string> resUniqueIdList;
	std::string resUniqueId;

    for(DownloadData::KVPairs kvValue : mLoadData->mPath2LDItem)
    {
		resUniqueId = kvValue.first;
        resUniqueIdList.add(resUniqueId);
    }

    int idx = 0;
    int len = resUniqueIdList.count();
    while (idx < len)
    {
        this->unloadNoRef(resUniqueIdList[idx]);
        ++idx;
    }

    resUniqueIdList.clear();
}

// 添加无引用资源到 List
void DownloadMgr::addNoRefResID2List(std::string resUniqueId)
{
    mZeroRefResIdList.add(resUniqueId);
}

// 卸载没有引用的资源列表中的资源
void DownloadMgr::unloadNoRefResFromList()
{
    for (std::string path : mZeroRefResIdList.getList())
    {
        if (mLoadData->mPath2LDItem[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
        {
            unloadNoRef(path);
        }
    }
    mZeroRefResIdList.clear();
}

// 不考虑引用计数，直接卸载
void DownloadMgr::unloadNoRef(std::string resUniqueId)
{
    if (UtilMap::ContainsKey(mLoadData->mPath2LDItem, resUniqueId))
    {
        mLoadData->mPath2LDItem[resUniqueId]->unload();
        mLoadData->mPath2LDItem[resUniqueId]->reset();
		UtilList::Add(mLoadData->mNoUsedLDItem, mLoadData->mPath2LDItem[resUniqueId]);
		UtilMap::Remove(mLoadData->mPath2LDItem, resUniqueId);

        // 检查是否存在还没有执行的 LoadItem，如果存在就直接移除
        removeWillLoadItem(resUniqueId);
    }
    else
    {
                
    }
}

void DownloadMgr::removeWillLoadItem(std::string resUniqueId)
{
    for (DownloadItem* loadItem : mLoadData->mWillLDItem)
    {
        if (loadItem->getResUniqueId() == resUniqueId)
        {
            releaseLoadItem(loadItem);      // 必然只有一个，如果有多个就是错误
            break;
        }
    }
}

void DownloadMgr::onLoadEventHandle(IDispatchObject* dispObj)
{
    DownloadItem* item = (DownloadItem*)dispObj;
    item->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&DownloadMgr::onLoadEventHandle
		)
	);

    if (item->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
    {
        onLoaded(item);
    }
    else if (item->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
    {
        onFailed(item);
    }

    item->getAllLoadResEventDispatch()->dispatchEvent(item);

    releaseLoadItem(item);
    --mCurNum;
    loadNextItem();
}

void DownloadMgr::onLoaded(DownloadItem* item)
{
	std::string resUniqueId = item->getResUniqueId();

    if (UtilMap::ContainsKey(mLoadData->mPath2LDItem, resUniqueId))
    {
        mLoadData->mPath2LDItem[item->getResUniqueId()]->init();
    }
    else        // 如果资源已经没有使用的地方了
    {
        item->unload();          // 直接卸载掉
    }
}

void DownloadMgr::onFailed(DownloadItem* item)
{
    std::string resUniqueId = item->getResUniqueId();
    if (UtilMap::ContainsKey(mLoadData->mPath2LDItem, resUniqueId))
    {
        mLoadData->mPath2LDItem[resUniqueId]->failed();
    }
}

void DownloadMgr::releaseLoadItem(DownloadItem* item)
{
	std::string resUniqueId = item->getResUniqueId();
    item->reset();
	UtilList::Add(mLoadData->mNoUsedLDItem, item);
	UtilList::Remove(mLoadData->mWillLDItem, item);
	UtilMap::Remove(mLoadData->mPath2LDItem, resUniqueId);
}

void DownloadMgr::loadNextItem()
{
    if (mCurNum < mMaxParral)
    {
		if (UtilList::Count(mLoadData->mWillLDItem) > 0)
        {
            std::string resUniqueId = mLoadData->mWillLDItem.front()->getResUniqueId();
            mLoadData->mPath2LDItem[resUniqueId] = mLoadData->mWillLDItem.front();
			UtilList::RemoveAt(mLoadData->mWillLDItem, 0);
            mLoadData->mPath2LDItem[resUniqueId]->load();

            ++mCurNum;
        }
    }
}

DownloadItem* DownloadMgr::findDownloadItemFormPool()
{
    mRetLoadItem = nullptr;
    for (DownloadItem* item : mLoadData->mNoUsedLDItem)
    {
        mRetLoadItem = item;
		UtilList::Remove(mLoadData->mNoUsedLDItem, mRetLoadItem);
        break;
    }

    return mRetLoadItem;
}

// 资源加载完成，触发下一次加载
void DownloadMgr::onMsgRouteResLoad(IDispatchObject* dispObj)
{
    /*MsgRouteBase msg = dispObj as MsgRouteBase;
    DownloadItem loadItem = (msg as LoadedWebResMR).m_task as DownloadItem;
    loadItem.handleResult();*/
}