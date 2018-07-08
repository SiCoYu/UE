#pragma once

#include "LuaBridgeInc.h"
#include "GObject.h"
#include "PlatformDefine.h"

//DECLARE_LOG_CATEGORY_EXTERN(LuaLog, Log, All);

MY_BEGIN_NAMESPACE(MyNS)

class MyLuaState;
class LuaFileUtil;

/**
* @brief 系统设置
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

	/**
	 * @param filename 这个是指 require 填入的 lua 模块的名字，例如 aaa.bbb.ccc ,不是完整的文件路径
	 */
	void doString(std::string chunk, std::string filename);
	void doFile(std::string fileName);

	void runLuaScript();
};

MY_END_NAMESPACE