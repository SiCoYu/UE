#include <MyProject.h>
#include "LuaSystem.h"
#include "LuaCppBind.h"
#include "MyLuaLoader.h"
#include "UtilEngineWrap.h"

//#include "MyScriptPlugin/Source/ScriptPlugin/Private/LuaIntegration.h"
// 相对于 MyProject\Plugins\MyScriptPlugin\Source
//#include "ScriptPlugin/Private/LuaIntegration.h"
//#include "ScriptPlugin/Classes/ScriptContext.h"
#include "ScriptPlugin/Classes/ScriptPluginExport.h"
//#include "LuaIntegration.h"

// 这两个接口不能导出来
// "ScriptPlugin/Private/LuaIntegration.cpp"
//extern void LuaRegisterUnrealUtilities(lua_State* LuaState);
// "GeneratedScriptLibraries.inl"
//extern void LuaRegisterExportedClasses(lua_State* InScriptContext);

LuaSystem::LuaSystem()
{
	this->L = nullptr;
}

LuaSystem::~LuaSystem()
{

}

void LuaSystem::init()
{
	// 打开基本库
	this->L = luaL_newstate();
	luaL_openlibs(this->L);

	// 导入 UE4 自己的类
	// 参考 MyProject\Plugins\MyScriptPlugin\Source\ScriptPlugin\Private\LuaIntegration.cpp
	// bool FLuaContext::Initialize(const FString& Code, UObject* Owner)
	//LuaRegisterExportedClasses(this->L);
	//LuaRegisterUnrealUtilities(this->L);
	//UScriptContext* a = UtilEngineWrap::NewObject<UScriptContext>();
	UScriptPluginExport::initPlugin(this->L);

	// 打开 Socket
	lua_getglobal(this->L, "package");
	lua_getfield(this->L, -1, "preload");

	lua_pushcfunction(this->L, luaopen_socket_core);
	lua_setfield(this->L, -2, "socket.core");

	lua_pushcfunction(this->L, luaopen_mime_core);
	lua_setfield(this->L, -2, "mime.core");

	lua_pop(this->L, 2);

	lua_settop(this->L, 0);

	// 绑定自定义加载器
	//addCClosureLualoader(this->L);
	addCFunctionLualoader(this->L);

	// 绑定外部库
	LuaCppBind::bind(this->L);
}

void LuaSystem::dispose()
{
	if (nullptr != this->L)
	{
		lua_close(L);
	}
}

lua_State* LuaSystem::getLuaVM()
{
	return this->L;
}

void LuaSystem::doString(std::string str)
{
	luaL_dostring(this->L, str.c_str());
}