#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MFileMode
{
	eCreateNew = 1,
	eCreate = 2,
	eOpen = 3,
	eOpenOrCreate = 4,
	eTruncate = 5,
	eAppend = 6
};

MY_END_NAMESPACE