#ifndef __CTX_H
#define __CTX_H

#include "Singleton.h"
#include "PlatformDefine.h"

#ifdef USE_EXTERN_THREAD
	#include <Sockets/StdoutLog.h>
#endif

class UIManager;
class UGameInstance;
class EngineData;
class EngineApi;
class INetMgr;
class TableSys;

#ifdef ENABLE_UNIT_TEST
	class Test;
#endif

class Ctx : public Singleton<Ctx>
{
protected:
	UIManager* m_uiMgr;
	EngineData* m_engineData;
	EngineApi* m_engineApi;
	INetMgr* m_pINetMgr;
	TableSys* m_pTableSys;

#ifdef USE_EXTERN_THREAD
	StdoutLog* m_pStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	Test* m_test;
#endif

public:
	Ctx();
	~Ctx();

	void init();
	void setUIMgr(UIManager* uiMgr);
	UIManager* getUIMgr();

	EngineData* getEngineData();
	EngineApi* getEngineApi();
	void setEngineApi(EngineApi* engineApi);
	void setNetMgr(INetMgr* pINetMgr);
	INetMgr* getNetMgr();
	TableSys* getTableSys();

#ifdef USE_EXTERN_THREAD
	StdoutLog* getStdLog();
#endif
};

#define g_pCtx Ctx::getSingletonPtr()
#define g_pTableSys Ctx::getSingletonPtr()->getTableSys()
#define g_pNetMgr Ctx::getSingletonPtr()->getNetMgr()
#define g_pUIMgr Ctx::getSingletonPtr()->getUIMgr()

#endif				// __CTX_H