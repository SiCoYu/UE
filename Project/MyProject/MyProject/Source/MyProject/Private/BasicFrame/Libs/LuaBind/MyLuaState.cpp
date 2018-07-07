#include <MyProject.h>
#include "MyLuaState.h"
#include "LuaCppBind.h"
#include "MyLuaLoader.h"
#include "UtilEngineWrap.h"

//#include "MyScriptPlugin/Source/ScriptPlugin/Private/LuaIntegration.h"
// ����� MyProject\Plugins\MyScriptPlugin\Source
//#include "ScriptPlugin/Private/LuaIntegration.h"
//#include "ScriptPlugin/Classes/ScriptContext.h"
#include "ScriptPlugin/Classes/ScriptPluginExport.h"
//#include "LuaIntegration.h"

// �������ӿڲ��ܵ�����
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
	// �򿪻�����
	this->mLuaState = luaL_newstate();
	luaL_openlibs(this->mLuaState);

	// ����ص�
	lua_atpanic(this->mLuaState, &LuaSystem::onLuaPanic);

	// ���� UE4 �Լ�����
	// �ο� MyProject\Plugins\MyScriptPlugin\Source\ScriptPlugin\Private\LuaIntegration.cpp
	// bool FLuaContext::Initialize(const FString& Code, UObject* Owner)
	//LuaRegisterExportedClasses(this->L);
	//LuaRegisterUnrealUtilities(this->L);
	//UScriptContext* a = UtilEngineWrap::NewObject<UScriptContext>();
	UScriptPluginExport::initPlugin(this->mLuaState);

	// �� Socket
	lua_getglobal(this->mLuaState, "package");
	lua_getfield(this->mLuaState, -1, "preload");

	lua_pushcfunction(this->mLuaState, luaopen_socket_core);
	lua_setfield(this->mLuaState, -2, "socket.core");

	lua_pushcfunction(this->mLuaState, luaopen_mime_core);
	lua_setfield(this->mLuaState, -2, "mime.core");

	lua_pop(this->mLuaState, 2);

	lua_settop(this->mLuaState, 0);

	// ���Զ��������
	//addCClosureLualoader(this->mLuaState);
	addCFunctionLualoader(this->mLuaState);

	// ���ⲿ��
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

void MyLuaState::doString(std::string str)
{
	luaL_dostring(this->mLuaState, str.c_str());
}

void MyLuaState::runLuaScript()
{
	// ���ֱ�ӵ����ǲ��ܳɹ�ִ�еģ������
	//loadLuaFromFile(this->mLuaState, "MyLua.Module.Entry.MainEntry");
	// ֻ���������ܳɹ�ִ�д���
	this->doString("require(\"MyLua.Module.Entry.MainEntry\")");
}

int32 MyLuaState::onLuaPanic(lua_State *lua_State)
{
	UE_LOG(LuaLog, Error, TEXT("PANIC: unprotected error in call to Lua API(%s)"), ANSI_TO_TCHAR(lua_tostring(lua_State, -1)));
	return 0;
}

void MyLuaState::onLuaError(std::string error)
{
	
}

protected void LuaLoadBuffer(byte[] buffer, string chunkName)
{
	LuaDLL.tolua_pushtraceback(L);
	int oldTop = LuaGetTop();

	if (LuaLoadBuffer(buffer, buffer.Length, chunkName) == 0)
	{
		if (LuaPCall(0, LuaDLL.LUA_MULTRET, oldTop) == 0)
		{
			LuaSetTop(oldTop - 1);
			return;
		}
	}

	string err = LuaToString(-1);
	LuaSetTop(oldTop - 1);
	throw new LuaException(err, LuaException.GetLastError());
}

protected void pushTraceback()
{

}

public int LuaGetTop()
{
	return lua_gettop(L);
}

public int LuaLoadBuffer(byte[] buff, int size, string name)
{
	return LuaDLL.luaL_loadbuffer(L, buff, size, name);
}

MY_END_NAMESPACE