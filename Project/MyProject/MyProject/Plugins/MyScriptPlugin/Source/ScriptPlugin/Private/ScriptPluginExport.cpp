#include "ScriptPluginExport.h"

//#define MY_ENABLE_CALL_LUA_REGISTER

// "ScriptPlugin/Private/LuaIntegration.cpp"
extern void LuaRegisterUnrealUtilities(lua_State* LuaState);
// "GeneratedScriptLibraries.inl"
#ifdef ENABLE_CALL_LUA_REGISTER
extern void LuaRegisterExportedClasses(lua_State* InScriptContext);
#endif

UScriptPluginExport::UScriptPluginExport(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UScriptPluginExport::initPlugin(lua_State* luaState)
{
#ifdef MY_ENABLE_CALL_LUA_REGISTER
	LuaRegisterExportedClasses(luaState);
#endif

	LuaRegisterUnrealUtilities(luaState);
}