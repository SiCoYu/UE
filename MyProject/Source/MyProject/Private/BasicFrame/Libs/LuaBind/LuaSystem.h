#pragma once

#include "LuaBridgeInc.h"

/**
* @brief ϵͳ����
*/
class LuaSystem
{
protected:
	lua_State* L;

public:
	LuaSystem();
	~LuaSystem();

protected:
	void init();
	void dispose();
};