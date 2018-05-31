#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 系统循环
 */
class ProcessSys : public GObject
{
public:
	ProcessSys();

public:
	void init();
	void dispose();

	void ProcessNextFrame();
	void Advance(float delta);
};

MY_END_NAMESPACE