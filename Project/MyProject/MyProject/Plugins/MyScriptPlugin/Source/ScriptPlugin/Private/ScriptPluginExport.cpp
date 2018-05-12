#include "ScriptPluginExport.h"

// "ScriptPlugin/Private/LuaIntegration.cpp"
extern void LuaRegisterUnrealUtilities(lua_State* LuaState);
// "GeneratedScriptLibraries.inl"
extern void LuaRegisterExportedClasses(lua_State* InScriptContext);

UScriptPluginExport::UScriptPluginExport(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UScriptPluginExport::initPlugin(lua_State* luaState)
{
	LuaRegisterExportedClasses(luaState);
	LuaRegisterUnrealUtilities(luaState);
}