#include "MyProject.h"
#include "LuaCppBind.h"

#include "TestClassBind.h"
#include "TestGlocalBind.h"

void LuaCppBind::bind(lua_State* L)
{
	TestClassBind::bind(L);
	TestGlocalBind::bind(L);
}