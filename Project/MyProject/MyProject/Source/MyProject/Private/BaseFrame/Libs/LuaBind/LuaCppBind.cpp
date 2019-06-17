#include "MyProject.h"
#include "LuaCppBind.h"

#include "TestClassBind.h"
#include "TestGlocalBind.h"

MY_BEGIN_NAMESPACE(MyNS)

void LuaCppBind::bind(lua_State* L)
{
	TestClassBind::bind(L);
	TestGlocalBind::bind(L);
}

MY_END_NAMESPACE