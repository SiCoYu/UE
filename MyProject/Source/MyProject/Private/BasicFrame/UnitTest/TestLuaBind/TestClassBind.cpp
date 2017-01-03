#include "MyProject.h"
#include "TestClassBind.h"
#include "TestClass.h"
#include "LuaBindInc.h"

void TestClassBind::bind(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginClass<TestClass>("TestClass")
		//.addConstructor<void(*)(void)>()  // ����ж�����캯��,��ֻ�ܵ���һ��
		.addConstructor<void(*)(const std::string&)>()
		.addFunction("getLength", &TestClass::Length)
		.addFunction("startWith", &TestClass::StartWith)
		.addCFunction("startWith", &TestClass::Lua_StartWith)
		.endClass();
}