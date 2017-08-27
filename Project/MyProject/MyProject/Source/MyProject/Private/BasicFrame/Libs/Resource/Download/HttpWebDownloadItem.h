#pragma once

#include "DownloadItem.h"

class HttpWeb;

/**
 * @brief 使用 HttpWeb 从网络下载数据
 */
class HttpWebDownloadItem : public DownloadItem
{
	typedef class DownloadItem Super;

protected:
	HttpWeb* mHttpWeb;

public:
	HttpWebDownloadItem();
	virtual ~HttpWebDownloadItem();

public:
	virtual void load() override;
    // 线程下载
	virtual void runTask() override;

protected:
    // 没有文件大小直接下载
	void downWithNoFileLen();
	// 根据文件大小下载
	void downWithFileLen();

	void onRunTaskEnd();

public:
    // 处理结果在这回调，然后分发给资源处理器，如果资源提前释放，就自动断开资源和加载器的事件分发就行了，不用在线程中处理了
	virtual void handleResult() override;
};