#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MTouchPhase
{
	Null,		// 未知状态
	Began,		// 开始
	Moved,		// 移动
	Stationary,	// 静止
	Ended,		// 结束
	Canceled,	// 取消
};

MY_END_NAMESPACE