#pragma once

#include <string>
#include <list>
#include "EventDispatchDelegate.h"
#include "MList.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 数据下载管理器
 */

class DownloadData;
class DownloadItem;
class DownloadParam;

//class DownloadMgr : MsgRouteHandleBase
class DownloadMgr : public GObject
{
protected:
    unsigned int mMaxParral;                             // 最多同时加载的内容
	unsigned int mCurNum;                                // 当前加载的数量
    DownloadData* mLoadData;
    DownloadItem* mRetLoadItem;
    //ResMsgRouteCB mResMsgRouteCB;
	MList<std::string> mZeroRefResIdList;      // 没有引用的资源 Id 列表
    int mLoadingDepth;                   // 加载深度

public:
	DownloadMgr();

public:
	void init();
	void dispose();

protected:
	void resetLoadParam(DownloadParam* loadParam);

public:
    // 是否有正在加载的 DownloadItem
	bool hasDownloadItem(std::string resUniqueId);

protected:
    // 重置加载设置
	void resetDownloadParam(DownloadParam* loadParam);

public:
    // 资源是否已经加载，包括成功和失败
	bool isDownloaded(std::string path);
	bool isSuccessDownLoaded(std::string resUniqueId);
	DownloadItem* getDownloadItem(std::string resUniqueId);

protected:
	DownloadItem* createDownloadItem(DownloadParam* param);
	void downloadWithDownloading(DownloadParam* param);
	void downloadWithNotDownload(DownloadParam* param);

public:
    // 通用类型，需要自己设置很多参数
	void download(DownloadParam* param);
	DownloadItem* getAndDownload(DownloadParam* param);
    // 这个卸载有引用计数，如果有引用计数就卸载不了
	void undownload(std::string resUniqueId, EventDispatchDelegate loadEventHandle);
    // 卸载所有的资源
	void unloadAll();

protected:
    // 添加无引用资源到 List
	void addNoRefResId2List(std::string resUniqueId);
    // 卸载没有引用的资源列表中的资源
	void unloadNoRefResFromList();
    // 不考虑引用计数，直接卸载
	void unloadNoRef(std::string resUniqueId);

public:
	void removeWillLoadItem(std::string resUniqueId);
	void onLoadEventHandle(IDispatchObject* dispObj);
	void onLoaded(DownloadItem* item);
	void onFailed(DownloadItem* item);

protected:
	void releaseLoadItem(DownloadItem* item);
	void loadNextItem();
	DownloadItem* findDownloadItemFormPool();
    // 资源加载完成，触发下一次加载
	void onMsgRouteResLoad(IDispatchObject* dispObj);
};

MY_END_NAMESPACE