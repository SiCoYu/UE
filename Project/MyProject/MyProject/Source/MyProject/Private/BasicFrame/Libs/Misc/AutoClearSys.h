#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MDataStream;

/**
 * @brief 覆盖安装后自动清理之前下载的数据，防止有老的数据存在
 */
class AutoClearSys
{
protected:
	std::string mInstallFlagFileFullPath;        // 检测的文件名字
    MDataStream* mDestDataStream;  // 目标保存的文件

public:
	AutoClearSys();

	void init();
	void dispose();

    // 是否是安装后第一次启动
	bool isFirstStartUpAfterInstalled();
    // 清理保存的文件
	void clearFiles();
    // 写入安装标志
	void writeInstallFlag();
	void checkAutoClear();
};

MY_END_NAMESPACE