#ifndef __CTX_H
#define __CTX_H

#include "Singleton.h"
#include "IUIManager.h"
#include <Sockets/StdoutLog.h>

class IUIManager;
class UGameInstance;
class EngineData;
class IEngineApi;
class INetMgr;

class Test;

class Ctx : public Singleton<Ctx>
{
protected:
	IUIManager* m_uiMgr;
	//UGameInstance* m_uGameInstance;
	EngineData* m_engineData;
	IEngineApi* m_engineApi;
	INetMgr* m_pINetMgr;
	StdoutLog* m_pStdoutLog;

	Test* m_test;

public:
	Ctx();
	~Ctx();

	void init();
	void setUIMgr(IUIManager* uiMgr);
	IUIManager* getUIMgr();
	//void setGameInstance(UGameInstance* ins);
	//UGameInstance* getGameInstance();

	EngineData* getEngineData();
	IEngineApi* getEngineApi();
	void setEngineApi(IEngineApi* engineApi);
	void setNetMgr(INetMgr* pINetMgr);
	INetMgr* getNetMgr();

	StdoutLog* getStdLog();
};

#endif				// __CTX_H