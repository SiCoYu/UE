#ifndef __CTX_H
#define __CTX_H

#include "Singleton.h"
#include "IUIManager.h"

class IUIManager;
class UGameInstance;
class EngineData;
class IEngineApi;

class Test;

class Ctx : public Singleton<Ctx>
{
protected:
	IUIManager* m_uiMgr;
	//UGameInstance* m_uGameInstance;
	EngineData* m_engineData;
	IEngineApi* m_engineApi;

	Test* m_test;

public:
	void init();
	void setUIMgr(IUIManager* uiMgr);
	IUIManager* getUIMgr();
	//void setGameInstance(UGameInstance* ins);
	//UGameInstance* getGameInstance();

	EngineData* getEngineData();
	IEngineApi* getEngineApi();
	void setEngineApi(IEngineApi* engineApi);
};

#endif				// __CTX_H