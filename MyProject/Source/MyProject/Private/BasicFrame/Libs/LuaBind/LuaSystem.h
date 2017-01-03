#pragma once

#include "LuaBridgeInc.h"

/**
* @brief œµÕ≥…Ë÷√
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