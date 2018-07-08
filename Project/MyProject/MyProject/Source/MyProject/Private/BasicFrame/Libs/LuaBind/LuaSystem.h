#pragma once

#include "LuaBridgeInc.h"
#include "GObject.h"
#include "PlatformDefine.h"

//DECLARE_LOG_CATEGORY_EXTERN(LuaLog, Log, All);

MY_BEGIN_NAMESPACE(MyNS)

class MyLuaState;
class LuaFileUtil;

/**
* @brief œµÕ≥…Ë÷√
*/
class LuaSystem : public GObject
{
public:
	//static int32 onLuaPanic(lua_State *lua_State);

protected:
	//lua_State* mLuaState;
	MyLuaState* mLuaState;
	LuaFileUtil* mLuaFileUtil;

public:
	LuaSystem();
	~LuaSystem();

public:
	void init();
	void dispose();

	LuaFileUtil* getLuaFileUtil();

	lua_State* getLuaVM();
	MyLuaState* getMyLuaState();

	void doString(std::string str);
	void doFile(std::string fileName);

	void runLuaScript();
};

MY_END_NAMESPACE