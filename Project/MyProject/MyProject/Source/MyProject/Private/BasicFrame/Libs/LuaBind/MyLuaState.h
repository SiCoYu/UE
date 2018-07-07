#pragma once

#include "LuaBridgeInc.h"
#include "GObject.h"
#include "PlatformDefine.h"

DECLARE_LOG_CATEGORY_EXTERN(LuaLog, Log, All);

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief œµÕ≥…Ë÷√
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
	void doString(const char* str);
	void doFile(const char* fileName);

	static int onLuaStackTrace(lua_State *lua_State);

protected:
	void _onLuaError(const char* error);
	void _LuaLoadBuffer(const char* buffer, size_t length, const char* chunkName);
};

MY_END_NAMESPACE