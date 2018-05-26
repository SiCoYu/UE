#pragma once

#include "GObject.h"

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