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

public:
	void init();
	void dispose();

	lua_State* getLuaVM();

	void doString(std::string str);
};