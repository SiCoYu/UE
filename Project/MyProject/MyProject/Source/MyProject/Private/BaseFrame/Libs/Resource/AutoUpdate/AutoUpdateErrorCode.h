#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 自动更新错误代码
 */
enum class AutoUpdateErrorCode
{
	eErrorNo,       // 没有错误
	eErrorDownloadWebVersionMiniFailed,     // 下载 Version_Mini.txt 失败
	eErrorDownloadWebVersionPFailed,        // 下载 Version_P.txt 失败
	eErrorDownloadWebResFailed,             // 下载 资源文件失败
};

MY_END_NAMESPACE