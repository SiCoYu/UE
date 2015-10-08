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
class LogSys;

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
	LogSys* m_pLogSys;

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
	UIManager* getUIMgrPtr();

	EngineData* getEngineDataPtr();
	EngineApi* getEngineApiPtr();
	void setEngineApiPtr(EngineApi* engineApi);
	void setNetMgrPtr(INetMgr* pINetMgr);
	INetMgr* getNetMgrPtr();
	TableSys* getTableSysPtr();
	LogSys* getLogSysPtr();

#ifdef USE_EXTERN_THREAD
	StdoutLog* getStdLog();
#endif
};

#define g_pCtx Ctx::getSingletonPtr()
#define g_pTableSys g_pCtx->getTableSysPtr()
#define g_pNetMgr g_pCtx->getNetMgrPtr()
#define g_pUIMgr g_pCtx->getUIMgrPtr()
#define g_pLogSys g_pCtx->getLogSysPtr();
#define g_pEngineData g_pCtx->getEngineDataPtr();
#define g_pEngineApi g_pCtx->getEngineApiPtr();

#endif				// __CTX_H