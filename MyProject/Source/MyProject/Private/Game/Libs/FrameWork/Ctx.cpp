#include "MyProject.h"
#include "Ctx.h"
#include "EngineData.h"
#include "INetMgr.h"
#include "UIMgr.h"
#include "NetMgr.h"
#include "EngineApi.h"
#include "TableSys.h"
#include "ShareData.h"
#include "NetDispList.h"
#include "LogSys.h"
#include "Config.h"
#include "LocalFileSys.h"
#include "PoolSys.h"
#include "UIAssetMgr.h"
#include "ResLoadMgr.h"

#ifdef ENABLE_UNIT_TEST
	#include "Test.h"
#endif

// 偏特化
template<> Ctx* Ctx::Singleton<Ctx>::m_sSingleton = 0;

Ctx::Ctx()
{
	
}

Ctx::~Ctx()
{
	delete m_uiMgr;
	delete m_engineData;
	delete m_pINetMgr;
	delete m_pTableSys;

#ifdef USE_EXTERN_THREAD
	delete m_pStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	delete m_test;
#endif

	delete m_pLogSys;
	delete m_pNetDispList;
	delete m_pShareData;
	delete m_pConfig;
	delete m_pLocalFileSys;
}

void Ctx::init()
{
	m_pShareData = new ShareData();
	m_pNetDispList = new NetDispList();
	m_pLogSys = new LogSys();
	m_engineData = new EngineData();
#ifdef USE_EXTERN_THREAD
	m_pStdoutLog = new StdoutLog();
#endif

	m_uiMgr = new UIMgr();
	m_pTableSys = new TableSys();
	m_pConfig = new Config();
	m_pLocalFileSys = new LocalFileSys();
#ifdef	USE_EXTERN_THREAD
	m_pINetMgr = new NetMgr(getStdLog());
#else
	m_pINetMgr = new NetMgr();
#endif

	// 挂在目录
	EngineApi::InsertMountPoint("/CacheData/", "E:/Self/Self/unreal/UE-GIT/UE-BP");

#ifdef ENABLE_UNIT_TEST
	m_test = new Test();
	m_test->runTest();
#endif

	testApi();
}

UIMgr* Ctx::getUIMgrPtr()
{
	return m_uiMgr;
}

EngineData* Ctx::getEngineDataPtr()
{
	return m_engineData;
}

void Ctx::setNetMgrPtr(INetMgr* pINetMgr)
{
	m_pINetMgr = pINetMgr;
}

INetMgr* Ctx::getNetMgrPtr()
{
	return m_pINetMgr;
}

#ifdef USE_EXTERN_THREAD
StdoutLog* Ctx::getStdLog()
{
	return m_pStdoutLog;
}
#endif

TableSys* Ctx::getTableSysPtr()
{
	return m_pTableSys;
}

LogSys* Ctx::getLogSysPtr()
{
	return m_pLogSys;
}

ShareData* Ctx::getShareDataPtr()
{
	return m_pShareData;
}

NetDispList* Ctx::getNetDispListPtr()
{
	return m_pNetDispList;
}

Config* Ctx::getConfigPtr()
{
	return m_pConfig;
}

LocalFileSys* Ctx::getLocalFileSysPtr()
{
	return m_pLocalFileSys;
}

PoolSys* Ctx::getPoolSysPtr()
{
	return m_poolSys;
}

UIAssetMgr* Ctx::getUIAssetMgrPtr()
{
	return m_uiAssetMgr;
}

ResLoadMgr* Ctx::getResLoadMgrPtr()
{
	return m_resLoadMgr;
}

void Ctx::testApi()
{
	EngineApi::GameUserDir();
}