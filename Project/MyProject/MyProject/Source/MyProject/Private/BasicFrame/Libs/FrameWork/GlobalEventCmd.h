#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 全局性的事件
*/
class GlobalEventCmd
{
public:
	GlobalEventCmd();

	void init();
	void dispose();
};

MY_END_NAMESPACE