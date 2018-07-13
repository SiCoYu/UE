#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MMountState
{
	eNull,		// 没有挂载
	eSuccess,	// 成功
	eFail,		// 失败
};

MY_END_NAMESPACE