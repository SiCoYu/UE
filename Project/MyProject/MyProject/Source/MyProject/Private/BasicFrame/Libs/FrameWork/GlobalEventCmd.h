#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 全局性的事件
*/
class GlobalEventCmd : public GObject
{
public:
	GlobalEventCmd();

	void init();
	void dispose();
};

MY_END_NAMESPACE