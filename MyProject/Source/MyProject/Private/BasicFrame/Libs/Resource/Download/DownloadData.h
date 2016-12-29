#pragma once

#include <map>
#include <string>
#include <list>

/**
 * @brief 下载数据
 */

class DownloadItem;

class DownloadData
{
public:
	typedef std::pair<std::string, DownloadItem*> KVPairs;

    // 因为资源有些需要协同程序，因此重复利用资源
	std::map<std::string, DownloadItem*> mPath2LDItem;       // 正在下载的内容 DownloadItem
	std::list<DownloadItem*> mWillLDItem;                           // 将要下载的 DownloadItem
	std::list<DownloadItem*> mNoUsedLDItem;                         // 没有被使用的 DownloadItem

public:
	DownloadData();
};