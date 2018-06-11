#pragma once

#include <string>
#include "MDiscreteList.h"
#include "MDictionary.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 下载数据
 */

class DownloadItem;

class DownloadData : public GObject
{
public:
	typedef std::pair<std::string, DownloadItem*> KVPairs;

    // 因为资源有些需要协同程序，因此重复利用资源
	MDictionary<std::string, DownloadItem*> mPath2LoadItemDic;       // 正在下载的内容 DownloadItem
	MDiscreteList<DownloadItem*> mWillLoadItemList;                           // 将要下载的 DownloadItem
	MDiscreteList<DownloadItem*> mNoUsedLoadItemList;                         // 没有被使用的 DownloadItem

public:
	DownloadData();

	void init();
	void dispose();
};

MY_END_NAMESPACE