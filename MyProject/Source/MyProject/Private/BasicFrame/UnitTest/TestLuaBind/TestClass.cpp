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
	bool ignore_spaces) const {
	size_t i = 0;

	if (ignore_spaces && !IsSpace(str[0])) {
		for (; i < data_.size() && IsSpace(data_[i]); ++i) {
		}
	}

	if (data_.size() < i + str.size()) {
		return false;
	}

	if (strncmp(&data_[i], &str[0], str.size()) == 0) {
		return true;
	}

	return false;
}

// Lua CFunction wrapper for StartWith.
int TestClass::Lua_StartWith(lua_State* L) {
	// 获取参数个数
	int n = lua_gettop(L);

	// 验证参数个数
	if (n != 3) {
		luaL_error(L, "incorrect argument number");
	}

	// 验证参数类型
	if (!lua_isstring(L, 2) || !lua_isboolean(L, 3)) {
		luaL_error(L, "incorrect argument type");
	}

	// 获取参数
	std::string str(lua_tostring(L, 2));
	bool ignore_spaces = lua_toboolean(L, 3) != 0;

	// 转调 StartWith
	int off = 0;
	bool result = StartWith(str, ignore_spaces, &off);

	// 返回结果
	luabridge::push(L, result);
	luabridge::push(L, off);
	return 2;  // 返回值有两个
}