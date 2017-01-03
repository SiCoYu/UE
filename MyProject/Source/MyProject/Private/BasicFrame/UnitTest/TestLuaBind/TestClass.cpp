#include "MyProject.h"
#include "TestClass.h"

TestClass::TestClass(const std::string& data)
	: data_(data) 
{

}

size_t TestClass::Length() const 
{
	return data_.length();
}

bool TestClass::StartWith(const std::string& str,
	bool ignore_spaces) {
	

	return false;
}

// Lua CFunction wrapper for StartWith.
int TestClass::Lua_StartWith(lua_State* L) {
	
	return 2;  // 返回值有两个
}