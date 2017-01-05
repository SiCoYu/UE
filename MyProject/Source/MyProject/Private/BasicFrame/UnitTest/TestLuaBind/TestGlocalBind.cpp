#include "MyProject.h"
#include "TestGlocalBind.h"
#include "TestGlocal.h"

void TestGlocalBind::bind(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.addFunction("sayHello", SayHello);
}