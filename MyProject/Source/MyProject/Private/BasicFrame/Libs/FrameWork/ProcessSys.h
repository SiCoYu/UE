#pragma once

/**
 * @brief 系统循环
 */
class ProcessSys
{
public:
	ProcessSys();

public:
	void init();
	void dispose();

	void ProcessNextFrame();
	void Advance(float delta);
};