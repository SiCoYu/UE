#pragma once

#include "LuaBridgeInc.h"
#include "GObject.h"
#include "PlatformDefine.h"

DECLARE_LOG_CATEGORY_EXTERN(LuaLog, Log, All);

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief ϵͳ����
*/
class MyLuaState : public GObject
{
public:
	static int32 onLuaPanic(lua_State *lua_State);

protected:
	lua_State* mLuaState;

public:
	MyLuaState();
	~MyLuaState();

public:
	void init();
	void dispose();

	lua_State* getLuaVM();
	void doString(std::string str);
	void runLuaScript();
};

MY_END_NAMESPACE