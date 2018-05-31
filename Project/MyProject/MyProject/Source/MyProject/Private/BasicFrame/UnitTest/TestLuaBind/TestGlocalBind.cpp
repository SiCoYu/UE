#include "MyProject.h"
#include "TestGlocalBind.h"
#include "TestGlocal.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestGlocalBind::bind(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.addFunction("sayHello", SayHello);
}

MY_END_NAMESPACE