#include <MyProject.h>
#include "MyLuaState.h"
#include <string>
#include "LuaCppBind.h"
#include "MyLuaLoader.h"
#include "UtilEngineWrap.h"
#include "UtilLuaSysLibWrap.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LuaSystem.h"
#include "LuaFileUtil.h"

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

DEFINE_LOG_CATEGORY(LuaLog);

MY_BEGIN_NAMESPACE(MyNS)

MyLuaState::MyLuaState()
{
	this->mLuaState = nullptr;
}

MyLuaState::~MyLuaState()
{

}

void MyLuaState::init()
{
	// 打开基本库
	this->mLuaState = luaL_newstate();
	luaL_openlibs(this->mLuaState);

	// 报错回调
	lua_atpanic(this->mLuaState, &MyLuaState::onLuaPanic);

	// 导入 UE4 自己的类
	// 参考 MyProject\Plugins\MyScriptPlugin\Source\ScriptPlugin\Private\LuaIntegration.cpp
	// bool FLuaContext::Initialize(const FString& Code, UObject* Owner)
	//LuaRegisterExportedClasses(this->L);
	//LuaRegisterUnrealUtilities(this->L);
	//UScriptContext* a = UtilEngineWrap::NewObject<UScriptContext>();
	UScriptPluginExport::initPlugin(this->mLuaState);

	// 打开 Socket
	lua_getglobal(this->mLuaState, "package");
	lua_getfield(this->mLuaState, -1, "preload");

	lua_pushcfunction(this->mLuaState, luaopen_socket_core);
	lua_setfield(this->mLuaState, -2, "socket.core");

	lua_pushcfunction(this->mLuaState, luaopen_mime_core);
	lua_setfield(this->mLuaState, -2, "mime.core");

	lua_pop(this->mLuaState, 2);

	lua_settop(this->mLuaState, 0);

	// 绑定自定义加载器
	//MyLuaLoader::addCClosureLualoader(this->mLuaState);
	MyLuaLoader::addCFunctionLualoader(this->mLuaState);

	// 绑定外部库
	LuaCppBind::bind(this->mLuaState);
}

void MyLuaState::dispose()
{
	if (nullptr != this->mLuaState)
	{
		lua_close(this->mLuaState);
		this->mLuaState = nullptr;
	}
}

lua_State* MyLuaState::getLuaVM()
{
	return this->mLuaState;
}

int32 MyLuaState::onLuaPanic(lua_State *lua_State)
{
	UE_LOG(LuaLog, Error, TEXT("PANIC: unprotected error in call to Lua API(%s)"), ANSI_TO_TCHAR(lua_tostring(lua_State, -1)));
	return 0;
}

void MyLuaState::onLuaError(const char* error)
{
	UE_LOG(LuaLog, Error, TEXT("PANIC: unprotected error in call to Lua API(%s)"), error);
}

int MyLuaState::onLuaStackTrace(lua_State *lua_State)
{
	const char* err = UtilLuaSysLibWrap::LuaToString(lua_State, -1);
	return 0;
}

void MyLuaState::doString(const char* str)
{
	luaL_dostring(this->mLuaState, str);
}

void MyLuaState::doFile(const char* fileName)
{
	const char* buffer = this->LoadFileBuffer(fileName);
	fileName = this->LuaChunkName(fileName);
	this->LuaLoadBuffer(buffer, fileName);
}

const char* MyLuaState::LoadFileBuffer(const char* fileName)
{
	int size = 0;
	const char* buffer = GLuaSystem->getLuaFileUtil()->ReadFile(fileName, size);

	if (buffer == nullptr)
	{
		string error = string.Format("cannot open {0}: No such file or directory", fileName);
		error += GLuaSystem->getLuaFileUtil()->FindFileError(fileName);
		this->onLuaError(error);
	}

	return buffer;
}

const char* MyLuaState::LuaChunkName(const char* name)
{
	std::string ret = "";

	if (MacroDef::ENABLE_LUA_DEBUG)
	{
		ret = GLuaSystem->getLuaFileUtil()->FindFile(name);
	}

	ret = "@" + ret;

	return ret.c_str();
}

void MyLuaState::LuaLoadBuffer(const char* buffer, size_t length, const char* chunkName)
{
	UtilLuaSysLibWrap::PushTraceback(this->mLuaState, &MyLuaState::onLuaStackTrace);
	int oldTop = UtilLuaSysLibWrap::LuaGetTop(this->mLuaState);

	if (UtilLuaSysLibWrap::LuaLoadBuffer(this->mLuaState, buffer, length, chunkName) == 0)
	{
		if (UtilLuaSysLibWrap::LuaPCall(this->mLuaState, 0, LUA_MULTRET, oldTop) == 0)
		{
			UtilLuaSysLibWrap::LuaSetTop(this->mLuaState, oldTop - 1);
			return;
		}
	}

	const char* err = UtilLuaSysLibWrap::LuaToString(this->mLuaState, -1);
	UtilLuaSysLibWrap::LuaSetTop(this->mLuaState, oldTop - 1);

	this->_onLuaError(err);
}

MY_END_NAMESPACE