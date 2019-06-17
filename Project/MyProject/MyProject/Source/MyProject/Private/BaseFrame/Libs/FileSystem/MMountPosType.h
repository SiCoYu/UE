#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MMountPosType
{
	eProject,		// 挂载到 Project ，目前挂载到工程师不能读取的
	eEngine,		// 挂在到 Engine，目前挂载到引擎是可以读取的
};

MY_END_NAMESPACE