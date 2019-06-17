#ifndef __TestClass_H
#define __TestClass_H

#include "CoreInc.h"
#include <string>
#include "LuaBindInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestClass : public GObject
{
public:
	TestClass(const std::string& data);
	size_t Length() const;
	bool IsSpace(char c);
	//bool StartWith(const std::string& str, bool ignore_spaces);
	bool StartWith(const std::string& str, bool ignore_spaces, int* off = NULL);
	int Lua_StartWith(lua_State* L);

private:
	std::string data_;
};

MY_END_NAMESPACE

#endif