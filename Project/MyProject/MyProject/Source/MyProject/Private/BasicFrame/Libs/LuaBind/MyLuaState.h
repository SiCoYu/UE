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
	static int onLuaStackTrace(lua_State *lua_State);
	static int32 onLuaPanic(lua_State *lua_State);

protected:
	lua_State* mLuaState;
	std::string mFileFullPath;

public:
	MyLuaState();
	~MyLuaState();

public:
	void init();
	void dispose();

	void onLuaError(const char* error);

	lua_State* getLuaVM();

	void doString(const char* chunk, const char* chunkName);
	void doFile(const char* fileName);

	void LuaLoadBuffer(const char* buffer, size_t length, const char* chunkName);
	const char* LoadFileBuffer(const char* fileName, int& outSize);
	const char* LuaChunkName(const char* name);

protected:
	void _registerEngineType();
	void _addLuaLoader();
	void _openLuaSocket();
};

MY_END_NAMESPACE