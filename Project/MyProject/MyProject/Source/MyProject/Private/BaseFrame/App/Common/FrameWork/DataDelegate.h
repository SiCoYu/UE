#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 全局性的事件
 */
class DataDelegate : public GObject
{
public:
	DataDelegate();

	void init();
	void dispose();
};

MY_END_NAMESPACE