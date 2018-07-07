#pragma once

#include "LuaBridgeInc.h"
#include "GObject.h"
#include "PlatformDefine.h"

DECLARE_LOG_CATEGORY_EXTERN(LuaLog, Log, All);

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief œµÕ≥…Ë÷√
*/
class LuaSystem : public GObject
{
public:
	static int32 onLuaPanic(lua_State *lua_State);

protected:
	lua_State* mLuaState;

public:
	LuaSystem();
	~LuaSystem();

public:
	void init();
	void dispose();

	lua_State* getLuaVM();
	void doString(std::string str);
	void doFile(std::string fileName);
	void runLuaScript();
};

MY_END_NAMESPACE