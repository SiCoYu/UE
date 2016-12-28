#pragma once

enum DownloadType
{
	eWWW,
	eHttpWeb,
	eTotal
};

#include <string>
#include "EventDispatchDelegate.h"
#include "ResLoadType.h"
#include "ResPackType.h"

/**
 * @brief 下载参数
 */
class DownloadParam
{
public:
    std::string mLoadPath;
	std::string mOrigPath;
	std::string mLogicPath;
	std::string mResUniqueId;
	std::string mExtName;
	std::string mVersion;

	EventDispatchDelegate mLoadEventHandle;
    DownloadType mDownloadType;
    ResLoadType mResLoadType;
    ResPackType mResPackType;

    bool mIsWriteFile;       // 下载完成是否写入文件
    long mFileLen;           // 文件长度，如果使用 HttpWeb 下载，使用这个字段判断文件长度

public:
	DownloadParam();

	void reset();
	void setPath(std::string origPath);
}