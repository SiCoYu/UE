#include "MyProject.h"
#include "Ctx.h"
#include "EngineData.h"

#include "EngineData.h"
#include "INetMgr.h"

#include "UIManager.h"
#include "EngineApi.h"
#include "NetMgr.h"

#include "Test.h"

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
	delete m_pStdoutLog;
	delete m_test;
}

void Ctx::init()
{
	m_engineData = new EngineData();
	m_pStdoutLog = new StdoutLog();

	m_uiMgr = new UIManager();
	m_engineApi = new EngineApi();
	m_pINetMgr = new NetMgr(getStdLog());

	m_test = new Test();
	m_test->runTest();
}

void Ctx::setUIMgr(IUIManager* uiMgr)
{
	m_uiMgr = uiMgr;
}

IUIManager* Ctx::getUIMgr()
{
	return m_uiMgr;
}

//void Ctx::setGameInstance(UGameInstance* ins)
//{
//	m_uGameInstance = ins;
//}
//
//UGameInstance* Ctx::getGameInstance()
//{
//	return m_uGameInstance;
//}

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

StdoutLog* Ctx::getStdLog()
{
	return m_pStdoutLog;
}