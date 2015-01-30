#include "MyProject.h"
#include "Ctx.h"

// Æ«ÌØ»¯
template<> Ctx* Ctx::Singleton<Ctx>::msSingleton = 0;

void Ctx::init()
{

}

void Ctx::initUIMgr(IUIManager* uiMgr)
{
	m_uiMgr = uiMgr;
}

IUIManager* Ctx::getUIMgr()
{
	return m_uiMgr;
}

void Ctx::setGameInstance(UGameInstance* ins)
{
	m_uGameInstance = ins;
}

UGameInstance* Ctx::getGameInstance()
{
	return m_uGameInstance;
}