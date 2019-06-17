#ifndef __LuaCFunction_H_
#define __LuaCFunction_H_

#include "lua.hpp"
#include "LuaCBase.h"
#include <vector>

class LuaCVM;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class LuaCFunction : public LuaCBase
{
protected:
	lua_State* L;

public:
	LuaCFunction(int reference, LuaCVM* interpreter);
	LuaCFunction(int reference, lua_State* l);
	~LuaCFunction();

	std::vector<LuaCObject*> call(std::vector<LuaCObject*> args, std::vector<int> returnTypes);
	std::vector<LuaCObject*> Call(std::vector<LuaCObject*> args);
	std::vector<LuaCObject*> Call();
	std::vector<LuaCObject*> Call(double arg1);
	int BeginPCall();
	bool PCall(int oldTop, int args);
	std::vector<LuaCObject*> PopValues(int oldTop);
	void EndPCall(int oldTop);
	lua_State* GetLuaState();
	void push(lua_State* luaState);
	void push();
	std::string ToString();
	int GetReference();
};

#endif