#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class LogDeviceType
{
	eWinLogDevice = 0,
	eNetLogDevice = 1,
	eFileLogDevice = 2,
};

MY_END_NAMESPACE