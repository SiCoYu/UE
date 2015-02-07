#include "MyProject.h"
#include "Ctx.h"
#include "EngineData.h"

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
	m_test = new Test();
	m_pStdoutLog = new StdoutLog();
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

IEngineApi* Ctx::getEngineApi()
{
	return m_engineApi;
}

void Ctx::setEngineApi(IEngineApi* engineApi)
{
	m_engineApi = engineApi;
}

void Ctx::setNetMgr(INetMgr* pINetMgr)
{
	m_pINetMgr = pINetMgr;
}

StdoutLog* Ctx::getStdLog()
{
	return m_pStdoutLog;
}