#include "MyProject.h"
#include "Ctx.h"
#include "EngineData.h"

// Æ«ÌØ»¯
template<> Ctx* Ctx::Singleton<Ctx>::msSingleton = 0;

void Ctx::init()
{
	m_engineData = new EngineData();
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