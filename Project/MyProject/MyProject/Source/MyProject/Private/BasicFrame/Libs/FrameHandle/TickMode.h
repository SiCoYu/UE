#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class TickMode
{
	eTM_Update,
	eTM_FixedUpdate,
	eTM_LateUpdate,
};

MY_END_NAMESPACE