#pragma once

#include "LuaBridgeInc.h"
#include "GObject.h"

/**
* @brief œµÕ≥…Ë÷√
*/
class LuaSystem : public GObject
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