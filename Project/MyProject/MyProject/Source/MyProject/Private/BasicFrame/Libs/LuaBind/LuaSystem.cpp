#include <MyProject.h>
#include "LuaSystem.h"
#include "LuaCppBind.h"
#include "MyLuaLoader.h"
#include "UtilEngineWrap.h"
#include "MyLuaState.h"
#include "LuaFileUtil.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "SafePointer.h"

//#include "MyScriptPlugin/Source/ScriptPlugin/Private/LuaIntegration.h"
// 相对于 MyProject\Plugins\MyScriptPlugin\Source
//#include "ScriptPlugin/Private/LuaIntegration.h"
//#include "ScriptPlugin/Classes/ScriptContext.h"
//#include "ScriptPlugin/Classes/ScriptPluginExport.h"
//#include "LuaIntegration.h"

// 这两个接口不能导出来
// "ScriptPlugin/Private/LuaIntegration.cpp"
//extern void LuaRegisterUnrealUtilities(lua_State* LuaState);
// "GeneratedScriptLibraries.inl"
//extern void LuaRegisterExportedClasses(lua_State* InScriptContext);

//DEFINE_LOG_CATEGORY(LuaLog);

MY_BEGIN_NAMESPACE(MyNS)

LuaSystem::LuaSystem()
{
	this->mLuaState = MY_NEW MyLuaState();
	this->mLuaFileUtil = MY_NEW LuaFileUtil();
}

LuaSystem::~LuaSystem()
{

}

void LuaSystem::init()
{
	// 打开基本库
	//this->mLuaState = luaL_newstate();
	//luaL_openlibs(this->mLuaState);

	// 报错回调
	//lua_atpanic(this->mLuaState, &LuaSystem::onLuaPanic);

	// 导入 UE4 自己的类
	// 参考 MyProject\Plugins\MyScriptPlugin\Source\ScriptPlugin\Private\LuaIntegration.cpp
	// bool FLuaContext::Initialize(const FString& Code, UObject* Owner)
	//LuaRegisterExportedClasses(this->L);
	//LuaRegisterUnrealUtilities(this->L);
	//UScriptContext* a = UtilEngineWrap::NewObject<UScriptContext>();
	//UScriptPluginExport::initPlugin(this->mLuaState);

	// 打开 Socket
	//lua_getglobal(this->mLuaState, "package");
	//lua_getfield(this->mLuaState, -1, "preload");

	//lua_pushcfunction(this->mLuaState, luaopen_socket_core);
	//lua_setfield(this->mLuaState, -2, "socket.core");

	//lua_pushcfunction(this->mLuaState, luaopen_mime_core);
	//lua_setfield(this->mLuaState, -2, "mime.core");

	//lua_pop(this->mLuaState, 2);

	//lua_settop(this->mLuaState, 0);

	// 绑定自定义加载器
	// MyLuaLoader::addCClosureLualoader(this->mLuaState);
	//MyLuaLoader::addCFunctionLualoader(this->mLuaState);

	// 绑定外部库
	//LuaCppBind::bind(this->mLuaState);

	this->mLuaState->init();
	this->mLuaFileUtil->init();
}

void LuaSystem::dispose()
{
	MY_SAFE_DISPOSE(this->mLuaState);
	MY_SAFE_DISPOSE(this->mLuaFileUtil);
}

LuaFileUtil* LuaSystem::getLuaFileUtil()
{
	return this->mLuaFileUtil;
}

lua_State* LuaSystem::getLuaVM()
{
	return this->mLuaState->getLuaVM();
}

MyLuaState* LuaSystem::getMyLuaState()
{
	return this->mLuaState;
}

/**
 * @param filename 这个是指 require 填入的 lua 模块的名字，例如 aaa.bbb.ccc ,不是完整的文件路径
 */
void LuaSystem::doString(std::string chunk, std::string filename)
{
	filename = this->mLuaState->LuaChunkName(filename.c_str());
	this->mLuaState->doString(chunk.c_str(), filename.c_str());
}

void LuaSystem::doFile(std::string fileName)
{
	this->mLuaState->doFile(fileName.c_str());
}

void LuaSystem::runLuaScript()
{
	// 这个仅仅是加载代码，如果要执行，还要调用 lua_pcall 才能执行
	//loadLuaFromFile(this->mLuaState, "MyLua.Module.Entry.MainEntry");
	// 这个是加载代码并执行，但是会先进入 LuaVM ，然后才加载
	//this->doString("require(\"MyLua.Module.Entry.MainEntry\")", "MyLua.Module.Entry.MainEntry");
	// 这个是加载代码并执行，不会先进入 LuaVM ，直接加载
	this->doFile("MyLua.Module.Entry.MainEntry");
}

//int32 LuaSystem::onLuaPanic(lua_State *lua_State)
//{
	//UE_LOG(LuaLog, Error, TEXT("PANIC: unprotected error in call to Lua API(%s)"), ANSI_TO_TCHAR(lua_tostring(lua_State, -1)));
	//return 0;
//}

MY_END_NAMESPACE