#ifndef __CTX_H
#define __CTX_H

#include "Singleton.h"
#include "PlatformDefine.h"

#ifdef USE_EXTERN_THREAD
	#include <Sockets/StdoutLog.h>
#endif

class UIMgr;
class UGameInstance;
class EngineData;
class EngineApi;
class INetMgr;
class TableSys;
class LogSys;
class ShareData;
class NetDispList;
class Config;
class LocalFileSys;
class PoolSys;
class UIAssetMgr;
class ResLoadMg;

#ifdef ENABLE_UNIT_TEST
	class Test;
#endif

class Ctx : public Singleton<Ctx>
{
protected:
	UIMgr* m_uiMgr;
	EngineData* m_engineData;
	EngineApi* m_engineApi;
	INetMgr* m_pINetMgr;
	TableSys* m_pTableSys;
	LogSys* m_pLogSys;
	ShareData* m_pShareData;
	NetDispList* m_pNetDispList;
	Config* m_pConfig;
	LocalFileSys* m_pLocalFileSys;
	PoolSys* m_poolSys;
	UIAssetMgr* m_uiAssetMgr;
	ResLoadMg* m_resLoadMgr;

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
	void setUIMgr(UIMgr* uiMgr);
	UIMgr* getUIMgrPtr();

	EngineData* getEngineDataPtr();
	EngineApi* getEngineApiPtr();
	void setEngineApiPtr(EngineApi* engineApi);
	void setNetMgrPtr(INetMgr* pINetMgr);
	INetMgr* getNetMgrPtr();
	TableSys* getTableSysPtr();
	LogSys* getLogSysPtr();
	ShareData* getShareDataPtr();
	NetDispList* getNetDispListPtr();
	Config* getConfigPtr();
	LocalFileSys* getLocalFileSysPtr();
	PoolSys* getPoolSysPtr();
	UIAssetMgr* getUIAssetMgrPtr();
	ResLoadMg* getResLoadMgrPtr();

	/**
	 *@brief 测试 Api，以后放到 UnitTest 中去
	 */
	void testApi();

#ifdef USE_EXTERN_THREAD
	StdoutLog* getStdLog();
#endif
};

#define g_pCtx Ctx::getSingletonPtr()
#define g_pTableSys g_pCtx->getTableSysPtr()
#define g_pNetMgr g_pCtx->getNetMgrPtr()
#define g_pUIMgr g_pCtx->getUIMgrPtr()
#define g_pLogSys g_pCtx->getLogSysPtr()
#define g_pEngineData g_pCtx->getEngineDataPtr()
#define g_pEngineApi g_pCtx->getEngineApiPtr()
#define g_pShareData g_pCtx->getShareDataPtr()
#define g_pNetDispList g_pCtx->getNetDispListPtr()
#define g_pCfg g_pCtx->getConfigPtr()
#define g_pLocalFileSys g_pCtx->getLocalFileSysPtr()
#define g_pPoolSys g_pCtx->getPoolSysPtr()
#define g_pUIAssetMgr g_pCtx->getUIAssetMgrPtr()
#define g_pResLoadMgr g_pCtx->getResLoadMgrPtr();

#endif				// __CTX_H