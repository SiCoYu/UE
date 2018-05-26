#pragma once

#include "GObject.h"

/**
 * @brief 主循环
 */
class EngineLoop : public GObject
{
public:
	EngineLoop();

public:
	void init();
	void dispose();

	void MainLoop();
	void FixedUpdate();
    // 循环执行完成后，再次
	void postUpdate();
};