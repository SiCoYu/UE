#include "MyProject.h"
#include "Ctx.h"
#include "EngineData.h"
#include "INetMgr.h"
#include "UIManager.h"
#include "EngineApi.h"
#include "NetMgr.h"
#include "TableSys.h"

#ifdef ENABLE_UNIT_TEST
	#include "Test.h"
#endif

// Æ«ÌØ»¯
template<> Ctx* Ctx::Singleton<Ctx>::m_sSingleton = 0;

Ctx::Ctx()
{
	
}

Ctx::~Ctx()
{
	delete m_uiMgr;
	delete m_engineData;
	delete m_engineApi;
	delete m_pINetMgr;
	delete m_pTableSys;

#ifdef USE_EXTERN_THREAD
	delete m_pStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	delete m_test;
#endif
}

void Ctx::init()
{
	m_engineData = new EngineData();
#ifdef USE_EXTERN_THREAD
	m_pStdoutLog = new StdoutLog();
#endif

	m_uiMgr = new UIManager();
	m_engineApi = new EngineApi();
	m_pTableSys = new TableSys();
	#ifdef	USE_EXTERN_THREAD
		m_pINetMgr = new NetMgr(getStdLog());
	#else
		m_pINetMgr = new NetMgr();
	#endif

#ifdef ENABLE_UNIT_TEST
	m_test = new Test();
	m_test->runTest();
#endif
}

void Ctx::setUIMgr(UIManager* uiMgr)
{
	m_uiMgr = uiMgr;
}

UIManager* Ctx::getUIMgr()
{
	return m_uiMgr;
}

EngineData* Ctx::getEngineData()
{
	return m_engineData;
}

EngineApi* Ctx::getEngineApi()
{
	return m_engineApi;
}

void Ctx::setEngineApi(EngineApi* engineApi)
{
	m_engineApi = engineApi;
}

void Ctx::setNetMgr(INetMgr* pINetMgr)
{
	m_pINetMgr = pINetMgr;
}

INetMgr* Ctx::getNetMgr()
{
	return m_pINetMgr;
}

#ifdef USE_EXTERN_THREAD
StdoutLog* Ctx::getStdLog()
{
	return m_pStdoutLog;
}
#endif

TableSys* Ctx::getTableSys()
{
	return m_pTableSys;
}