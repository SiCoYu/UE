#include "MyProject.h"
#include "DownloadMgr.h"
#include "DownloadData.h"
#include "DownloadParam.h"
#include "DownloadItem.h"
#include "ResLoadState.h"
#include "HttpWebDownloadItem.h"
#include "RefCount.h"

MY_BEGIN_NAMESPACE(MyNS)

DownloadMgr::DownloadMgr()
{
    this->mMaxParral = 8;
	this->mCurNum = 0;
	this->mLoadData = MY_NEW DownloadData();
	this->mLoadingDepth = 0;

    //this->addMsgRouteHandle(MsgRouteId.eMRIDLoadedWebRes, onMsgRouteResLoad);
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

	for (DownloadData::KVPairs kvValue : this->mLoadData->mPath2LDItem.getData())
    {
		loadItemValue = kvValue.second;

        if (loadItemValue->getResUniqueId() == resUniqueId)
        {
            return true;
        }
    }

    for (DownloadItem* loadItem : this->mLoadData->mWillLDItem)
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

    for (DownloadData::KVPairs kvValue : this->mLoadData->mPath2LDItem.getData())
    {
		loadItemValue = kvValue.second;

        if (loadItemValue->getResUniqueId() == resUniqueId)
        {
            return loadItemValue;
        }
    }

    for (DownloadItem* loadItem : this->mLoadData->mWillLDItem)
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
    DownloadItem* loadItem = this->findDownloadItemFormPool();
    if (loadItem == nullptr)
    {
        if (param->mDownloadType == eHttpWeb)
        {
            loadItem = MY_NEW HttpWebDownloadItem();
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
	this->mLoadData->mPath2LDItem[param->mResUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->incRef();
    if (this->mLoadData->mPath2LDItem[param->mResUniqueId]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
    {
        if (param->mLoadEventHandle != nullptr)
        {
            param->mLoadEventHandle(this->mLoadData->mPath2LDItem[param->mResUniqueId]);
        }
    }
    else
    {
        if (param->mLoadEventHandle != nullptr)
        {
			this->mLoadData->mPath2LDItem[param->mResUniqueId]->getAllLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);
        }
    }

	this->resetLoadParam(param);
}

void DownloadMgr::downloadWithNotDownload(DownloadParam* param)
{
    if (!this->hasDownloadItem(param->mResUniqueId))
    {
        DownloadItem* loadItem = this->createDownloadItem(param);

        if (this->mCurNum < this->mMaxParral)
        {
            // 先增加，否则退出的时候可能是先减 1 ，导致越界出现很大的值
            ++this->mCurNum;
			this->mLoadData->mPath2LDItem[param->mResUniqueId] = loadItem;
			this->mLoadData->mPath2LDItem[param->mResUniqueId]->load();
        }
        else
        {
            UtilList::Add(this->mLoadData->mWillLDItem, loadItem);
        }
    }

	this->resetLoadParam(param);
}

// 通用类型，需要自己设置很多参数
void DownloadMgr::download(DownloadParam* param)
{
    ++this->mLoadingDepth;

    if (UtilMap::ContainsKey(this->mLoadData->mPath2LDItem.getData(), param->mResUniqueId))
    {
		this->downloadWithDownloading(param);
    }
    else
    {
		this->downloadWithNotDownload(param);
    }

    --this->mLoadingDepth;

    if (this->mLoadingDepth == 0)
    {
		this->unloadNoRefResFromList();
    }
}

DownloadItem* DownloadMgr::getAndDownload(DownloadParam* param)
{
    //param.resolvePath();
	this->download(param);
    return this->getDownloadItem(param->mResUniqueId);
}

// 这个卸载有引用计数，如果有引用计数就卸载不了
void DownloadMgr::undownload(std::string resUniqueId, EventDispatchDelegate loadEventHandle)
{
    if (UtilMap::ContainsKey(this->mLoadData->mPath2LDItem.getData(), resUniqueId))
    {
        // 移除事件监听器，因为很有可能移除的时候，资源还没加载完成，这个时候事件监听器中的处理函数列表还没有清理
		this->mLoadData->mPath2LDItem[resUniqueId]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		this->mLoadData->mPath2LDItem[resUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->decRef();
        if (this->mLoadData->mPath2LDItem[resUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
        {
            if (this->mLoadingDepth != 0)
            {
				this->addNoRefResID2List(resUniqueId);
            }
            else
            {
				this->unloadNoRef(resUniqueId);
            }
        }
    }
}

// 卸载所有的资源
void DownloadMgr::unloadAll()
{
    MList<std::string> resUniqueIdList;
	std::string resUniqueId;

    for(DownloadData::KVPairs kvValue : this->mLoadData->mPath2LDItem)
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
	this->mZeroRefResIdList.add(resUniqueId);
}

// 卸载没有引用的资源列表中的资源
void DownloadMgr::unloadNoRefResFromList()
{
    for (std::string path : this->mZeroRefResIdList.getList())
    {
        if (this->mLoadData->mPath2LDItem[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
        {
			this->unloadNoRef(path);
        }
    }

	this->mZeroRefResIdList.clear();
}

// 不考虑引用计数，直接卸载
void DownloadMgr::unloadNoRef(std::string resUniqueId)
{
    if (UtilMap::ContainsKey(this->mLoadData->mPath2LDItem, resUniqueId))
    {
		this->mLoadData->mPath2LDItem[resUniqueId]->unload();
		this->mLoadData->mPath2LDItem[resUniqueId]->reset();
		UtilList::Add(this->mLoadData->mNoUsedLDItem, this->mLoadData->mPath2LDItem[resUniqueId]);
		UtilMap::Remove(this->mLoadData->mPath2LDItem, resUniqueId);

        // 检查是否存在还没有执行的 LoadItem，如果存在就直接移除
		this->removeWillLoadItem(resUniqueId);
    }
    else
    {
                
    }
}

void DownloadMgr::removeWillLoadItem(std::string resUniqueId)
{
    for (DownloadItem* loadItem : this->mLoadData->mWillLDItem)
    {
        if (loadItem->getResUniqueId() == resUniqueId)
        {
			this->releaseLoadItem(loadItem);      // 必然只有一个，如果有多个就是错误
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
		this->onLoaded(item);
    }
    else if (item->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
    {
		this->onFailed(item);
    }

    item->getAllLoadResEventDispatch()->dispatchEvent(item);

	this->releaseLoadItem(item);
    --this->mCurNum;
	this->loadNextItem();
}

void DownloadMgr::onLoaded(DownloadItem* item)
{
	std::string resUniqueId = item->getResUniqueId();

    if (UtilMap::ContainsKey(this->mLoadData->mPath2LDItem, resUniqueId))
    {
		this->mLoadData->mPath2LDItem[item->getResUniqueId()]->init();
    }
    else        // 如果资源已经没有使用的地方了
    {
        item->unload();          // 直接卸载掉
    }
}

void DownloadMgr::onFailed(DownloadItem* item)
{
    std::string resUniqueId = item->getResUniqueId();
    if (UtilMap::ContainsKey(this->mLoadData->mPath2LDItem, resUniqueId))
    {
		this->mLoadData->mPath2LDItem[resUniqueId]->failed();
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
    if (this->mCurNum < this->mMaxParral)
    {
		if (UtilList::Count(this->mLoadData->mWillLDItem) > 0)
        {
            std::string resUniqueId = this->mLoadData->mWillLDItem.front()->getResUniqueId();
			this->mLoadData->mPath2LDItem[resUniqueId] = this->mLoadData->mWillLDItem.front();
			UtilList::RemoveAt(this->mLoadData->mWillLDItem, 0);
			this->mLoadData->mPath2LDItem[resUniqueId]->load();

            ++this->mCurNum;
        }
    }
}

DownloadItem* DownloadMgr::findDownloadItemFormPool()
{
	this->mRetLoadItem = nullptr;

    for (DownloadItem* item : this->mLoadData->mNoUsedLDItem)
    {
		this->mRetLoadItem = item;
		UtilList::Remove(this->mLoadData->mNoUsedLDItem, this->mRetLoadItem);
        break;
    }

    return this->mRetLoadItem;
}

// 资源加载完成，触发下一次加载
void DownloadMgr::onMsgRouteResLoad(IDispatchObject* dispObj)
{
    /*MsgRouteBase msg = dispObj as MsgRouteBase;
    DownloadItem loadItem = (msg as LoadedWebResMR).m_task as DownloadItem;
    loadItem.handleResult();*/
}

MY_END_NAMESPACE