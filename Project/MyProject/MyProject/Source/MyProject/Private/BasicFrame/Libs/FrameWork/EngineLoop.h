#pragma once

/**
 * @brief 主循环
 */
class EngineLoop
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