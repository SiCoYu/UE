#pragma once

#include <string>
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class FileVerInfo : public GObject
{
public:
	std::string mOrigPath;    // 原始加载路径
	std::string mResUniqueId; // 资源唯一ID
	std::string mLoadPath;    // 加载的目录
	std::string mFileMd5;    // 文件 md5
    int mFileSize;      // 文件大小

public:
	void init();
	void dispose();

	bool isNoVerInfo();
};

MY_END_NAMESPACE