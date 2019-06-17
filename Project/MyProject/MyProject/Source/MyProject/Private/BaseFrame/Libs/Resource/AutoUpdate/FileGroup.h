#pragma once

#include <string>
#include "MList.h"
#include "GObject.h"
#include "EventDispatchDelegate.h"
#include "MDictionary.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;
class FileVerInfo;

/**
 * @brief 一组文件的统计信息
 */
class FileGroup : public GObject
{
protected:
	int mCurNum;          // 当前已经更新的资源数量
	int mTotalNum;        // 总共需要更新的资源数量
	int mCurMemSize;      // 当前资源内存总共大小，单位 byte
	int mTotalMemSize;    // 总共资源内存总共大小，单位 byte

	MList<std::string> mLoadingPath;       // 将要下载
	MList<std::string> mLoadedPath;        // 已经下载成功
	MList<std::string> mFailedPath;        // 下载失败

	MDictionary<std::string, bool> mUpdatePathDic;    // 更新的资源目录

	AddOnceEventDispatch* mProgressDispatch;   // 进度事件分发

public:
	FileGroup();

	bool isUpdateSuccess();
	bool isCurEqTotal();
	void reset();
	void setTotalNum(int value);

	int getTotalNum();
	void incCurNum();
	int getCurNum();
	// 有正在加载的内容
	bool hasLoading();
	// 有加载失败的
	bool hasLoadFailed();

	// 增加更新的文件
	void addLoadingPath(std::string& path, FileVerInfo* fileVerInfo /*, bool isAddTotalNum = false*/);
	void removeLoadingPath(std::string& path/*, bool isDecTotalNum = false*/);
	void addLoadedPath(std::string& path/*, bool isAddTotalNum = false*/);
	void addFailedPath(std::string& path/*, bool isAddTotalNum = false*/);
	// 获取进度 [0, 100]
	int getProgress();

	// 获取文件加载内存大小
	int getAllNeedUpdateMenSize();
	// 获取当前加载的文件大小
	int getCurUpdatedMenSize();
	// 获取加载进度描述
	std::string getProgressDesc();
	// 输出下载详细日志
	void logDownloadDetailInfo();

	// 获取当前资源是否更新了
	bool isResUpdatedByResPath(std::string path);
	// 获取当前资源是否更新了
	bool isResUpdatedByABPath(std::string path);
	void addProgressHandle(EventDispatchDelegate handle);
	void removeProgressHandle(EventDispatchDelegate handle);
};

MY_END_NAMESPACE