#include "MyProject.h"
#include "TestClass.h"

MY_BEGIN_NAMESPACE(MyNS)

TestClass::TestClass(const std::string& data)
	: data_(data)
{

}

size_t TestClass::Length() const
{
	return data_.length();
}

bool TestClass::IsSpace(char c)
{
	return c == ' ' || c == '\t';
}

//bool TestClass::StartWith(const std::string& str, bool ignore_spaces)
//{
//	size_t i = 0;
//
//	if (ignore_spaces && !IsSpace(str[0]))
//	{
//		for (; i < data_.size() && IsSpace(data_[i]); ++i)
//		{
//		}
//	}
//
//	if (data_.size() < i + str.size())
//	{
//		return false;
//	}
//
//	if (strncmp(&data_[i], &str[0], str.size()) == 0)
//	{
//		return true;
//	}
//
//	return false;
//}

bool TestClass::StartWith(const std::string& str, bool ignore_spaces, int* off)
{
	size_t i = 0;

	if (ignore_spaces && !IsSpace(str[0]))
	{
		for (; i < data_.size() && IsSpace(data_[i]); ++i)
		{
		}
	}

	if (data_.size() < i + str.size())
	{
		return false;
	}

	if (strncmp(&data_[i], &str[0], str.size()) == 0)
	{
		if (off != NULL)
		{
			*off = static_cast<int>(i);
		}
		return true;
	}

	return false;
}

// Lua CFunction wrapper for StartWith.
int TestClass::Lua_StartWith(lua_State* L)
{
	// 获取参数个数
	int n = lua_gettop(L);

	// 验证参数个数
	if (n != 3)
	{
		luaL_error(L, "incorrect argument number");
	}

	// 验证参数类型
	if (!lua_isstring(L, 2) || !lua_isboolean(L, 3))
	{
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

//int Line::Lua_StartWith(lua_State* L) 
//{
//	int n = lua_gettop(L);
//
//	if (n < 3) 
//	{
//		luaL_error(L, "incorrect argument number");
//	}
//
//	if (!lua_isboolean(L, 2)) 
//	{
//		luaL_error(L, "incorrect argument type");
//	}
//
//	bool ignore_spaces = lua_toboolean(L, 2) != 0;
//
//	bool result = false;
//	int off = 0;
//
//	// 逐个比较字符串变参，一旦匹配就跳出循环。
//	for (int i = 3; i <= n; ++i) 
//	{
//		if (!lua_isstring(L, i)) 
//		{
//			break;
//		}
//		std::string str(lua_tostring(L, i));
//		if (StartWith(str, ignore_spaces, &off)) 
//		{
//			result = true;
//			break;
//		}
//	}
//
//	luabridge::push(L, result);
//	luabridge::push(L, off);
//	return 2;
//}

MY_END_NAMESPACE