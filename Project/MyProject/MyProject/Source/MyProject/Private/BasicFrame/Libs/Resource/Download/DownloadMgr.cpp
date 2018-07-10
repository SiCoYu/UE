#include "MyProject.h"
#include "DownloadMgr.h"
#include "DownloadData.h"
#include "DownloadParam.h"
#include "DownloadItem.h"
#include "ResLoadState.h"
#include "HttpWebDownloadItem.h"
#include "RefCount.h"
#include "SafePointer.h"
#include "Ctx.h"
#include "LogTypeId.h"
#include "LogSys.h"

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
	MY_SAFE_DISPOSE(this->mLoadData);
}

void DownloadMgr::resetLoadParam(DownloadParam* loadParam)
{
    loadParam->reset();
}

// 是否有正在加载的 DownloadItem
bool DownloadMgr::hasDownloadItem(std::string resUniqueId)
{
	DownloadItem* loadItemValue = nullptr;

	for (DownloadData::KVPairs kvValue : this->mLoadData->mPath2LoadItemDic.getData())
    {
		loadItemValue = kvValue.second;

        if (loadItemValue->getResUniqueId() == resUniqueId)
        {
            return true;
        }
    }

    for (DownloadItem* loadItem : this->mLoadData->mWillLoadItemList.getList())
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
	bool ret = false;

    DownloadItem* downloadItem = this->getDownloadItem(path);
    if (downloadItem == nullptr)
    {
        ret = false;
    }
    else if (downloadItem->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded() ||
        downloadItem->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
    {
        ret = true;
    }

    return ret;
}

bool DownloadMgr::isSuccessDownLoaded(std::string resUniqueId)
{
	bool ret = false;

    DownloadItem* downloadItem = this->getDownloadItem(resUniqueId);
    if (downloadItem == nullptr)
    {
		ret = false;
    }
    else if (downloadItem->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
    {
		ret = true;
    }

    return ret;
}

DownloadItem* DownloadMgr::getDownloadItem(std::string resUniqueId)
{
	DownloadItem* loadItemValue = nullptr;

    for (DownloadData::KVPairs kvValue : this->mLoadData->mPath2LoadItemDic.getData())
    {
		loadItemValue = kvValue.second;

        if (loadItemValue->getResUniqueId() == resUniqueId)
        {
            return loadItemValue;
        }
    }

    for (DownloadItem* loadItem : this->mLoadData->mWillLoadItemList.getList())
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
        if (param->mDownloadType == DownloadType::eHttpWeb)
        {
            loadItem = MY_NEW HttpWebDownloadItem();
        }
    }

    loadItem->setLoadParam(param);

    loadItem->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&DownloadMgr::onLoadEventHandle,
			(uint)0
		)
	);

    loadItem->getAllLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);

    return loadItem;
}

void DownloadMgr::downloadWithDownloading(DownloadParam* param)
{
	this->mLoadData->mPath2LoadItemDic[param->mResUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->incRef();

    if (this->mLoadData->mPath2LoadItemDic[param->mResUniqueId]->getRefCountResLoadResultNotify()->getResLoadState()->hasLoaded())
    {
        if (!param->mLoadEventHandle.empty())
        {
            param->mLoadEventHandle(
				this->mLoadData->mPath2LoadItemDic[param->mResUniqueId]
			);
        }
    }
    else
    {
        if (!param->mLoadEventHandle.empty())
        {
			this->mLoadData->mPath2LoadItemDic[param->mResUniqueId]->getAllLoadResEventDispatch()->addEventHandle(param->mLoadEventHandle);
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

			this->mLoadData->mPath2LoadItemDic[param->mResUniqueId] = loadItem;
			this->mLoadData->mPath2LoadItemDic[param->mResUniqueId]->load();
        }
        else
        {
            this->mLoadData->mWillLoadItemList.add(loadItem);
        }
    }

	this->resetLoadParam(param);
}

// 通用类型，需要自己设置很多参数
void DownloadMgr::download(DownloadParam* param)
{
    ++this->mLoadingDepth;

    if (this->mLoadData->mPath2LoadItemDic.containsKey(param->mResUniqueId))
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
    if (this->mLoadData->mPath2LoadItemDic.containsKey(resUniqueId))
    {
        // 移除事件监听器，因为很有可能移除的时候，资源还没加载完成，这个时候事件监听器中的处理函数列表还没有清理
		this->mLoadData->mPath2LoadItemDic[resUniqueId]->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(loadEventHandle);
		this->mLoadData->mPath2LoadItemDic[resUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->decRef();

        if (this->mLoadData->mPath2LoadItemDic[resUniqueId]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
        {
            if (this->mLoadingDepth != 0)
            {
				this->addNoRefResId2List(resUniqueId);
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

    for(DownloadData::KVPairs kvValue : this->mLoadData->mPath2LoadItemDic.getData())
    {
		resUniqueId = kvValue.first;
        resUniqueIdList.add(resUniqueId);
    }

    int index = 0;
    int len = resUniqueIdList.count();

    while (index < len)
    {
        this->unloadNoRef(resUniqueIdList[index]);
        ++index;
    }

    resUniqueIdList.clear();
}

// 添加无引用资源到 List
void DownloadMgr::addNoRefResId2List(std::string resUniqueId)
{
	this->mZeroRefResIdList.add(resUniqueId);
}

// 卸载没有引用的资源列表中的资源
void DownloadMgr::unloadNoRefResFromList()
{
    for (std::string path : this->mZeroRefResIdList.getList())
    {
        if (this->mLoadData->mPath2LoadItemDic[path]->getRefCountResLoadResultNotify()->getRefCount()->isNoRef())
        {
			this->unloadNoRef(path);
        }
    }

	this->mZeroRefResIdList.clear();
}

// 不考虑引用计数，直接卸载
void DownloadMgr::unloadNoRef(std::string resUniqueId)
{
    if (this->mLoadData->mPath2LoadItemDic.containsKey(resUniqueId))
    {
		this->mLoadData->mPath2LoadItemDic[resUniqueId]->unload();
		this->mLoadData->mPath2LoadItemDic[resUniqueId]->reset();
		this->mLoadData->mNoUsedLoadItemList.add(this->mLoadData->mPath2LoadItemDic[resUniqueId]);
		this->mLoadData->mPath2LoadItemDic.remove(resUniqueId);

        // 检查是否存在还没有执行的 LoadItem，如果存在就直接移除
		this->removeWillLoadItem(resUniqueId);
    }
    else
    {
		GLogSys->log("DownloadMgr::unloadNoRef, no resUniqueId", LogTypeId::eLogDownload);
    }
}

void DownloadMgr::removeWillLoadItem(std::string resUniqueId)
{
    for (DownloadItem* loadItem : this->mLoadData->mWillLoadItemList.getList())
    {
        if (loadItem->getResUniqueId() == resUniqueId)
        {
			this->releaseLoadItem(loadItem);      // 必然只有一个，如果有多个就是错误
            break;
        }
    }
}

void DownloadMgr::onLoadEventHandle(uint eventId, IDispatchObject* dispObj)
{
    DownloadItem* item = (DownloadItem*)dispObj;
    item->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->removeEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&DownloadMgr::onLoadEventHandle, 
			(uint)0
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

    if (this->mLoadData->mPath2LoadItemDic.containsKey(resUniqueId))
    {
		this->mLoadData->mPath2LoadItemDic[resUniqueId]->init();
    }
    else        // 如果资源已经没有使用的地方了
    {
        item->unload();          // 直接卸载掉
    }
}

void DownloadMgr::onFailed(DownloadItem* item)
{
    std::string resUniqueId = item->getResUniqueId();
    if (this->mLoadData->mPath2LoadItemDic.containsKey(resUniqueId))
    {
		this->mLoadData->mPath2LoadItemDic[resUniqueId]->failed();
    }
}

void DownloadMgr::releaseLoadItem(DownloadItem* item)
{
	std::string resUniqueId = item->getResUniqueId();
    item->reset();
	this->mLoadData->mNoUsedLoadItemList.add(item);
	this->mLoadData->mWillLoadItemList.remove(item);
	this->mLoadData->mPath2LoadItemDic.remove(resUniqueId);
}

void DownloadMgr::loadNextItem()
{
    if (this->mCurNum < this->mMaxParral)
    {
		if (this->mLoadData->mWillLoadItemList.count() > 0)
        {
            std::string resUniqueId = this->mLoadData->mWillLoadItemList.get(0)->getResUniqueId();
			this->mLoadData->mPath2LoadItemDic[resUniqueId] = this->mLoadData->mWillLoadItemList.get(0);

			this->mLoadData->mWillLoadItemList.removeAt(0);
			this->mLoadData->mPath2LoadItemDic[resUniqueId]->load();

            ++this->mCurNum;
        }
    }
}

DownloadItem* DownloadMgr::findDownloadItemFormPool()
{
	this->mRetLoadItem = nullptr;

    for (DownloadItem* item : this->mLoadData->mNoUsedLoadItemList.getList())
    {
		this->mRetLoadItem = item;
		this->mLoadData->mNoUsedLoadItemList.remove(this->mRetLoadItem);
        break;
    }

    return this->mRetLoadItem;
}

// 资源加载完成，触发下一次加载
void DownloadMgr::onMsgRouteResLoad(uint eventId, IDispatchObject* dispObj)
{
    //MsgRouteBase msg = dispObj as MsgRouteBase;
    //DownloadItem loadItem = (msg as LoadedWebResMR).m_task as DownloadItem;
    //loadItem.handleResult();
}

MY_END_NAMESPACE