#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class FileOpState
{
	eNoOp = 0,      // 无操作
	eOpening = 1,   // 打开中
	eOpenSuccess = 2,   // 打开成功
	eOpenFail = 3,      // 打开失败
	eOpenClose = 4,     // 关闭
};

MY_END_NAMESPACE