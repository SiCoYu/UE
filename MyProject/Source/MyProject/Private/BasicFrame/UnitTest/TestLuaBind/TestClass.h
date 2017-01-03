#ifndef __TestClass_H
#define __TestClass_H

#include "CoreInc.h"
#include <string>
#include "LuaBindInc.h"

class TestClass : public GObject
{
public:
	TestClass(const std::string& data);
	size_t Length() const;
	bool StartWith(const std::string& str,
		bool ignore_spaces);
	int Lua_StartWith(lua_State* L);

private:
	std::string data_;
};

#endif