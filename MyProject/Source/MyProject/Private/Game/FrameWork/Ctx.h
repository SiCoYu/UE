#ifndef __CTX_H
#define __CTX_H

#include "Singleton.h"
#include <Sockets/StdoutLog.h>

class UIManager;
class UGameInstance;
class EngineData;
class EngineApi;
class INetMgr;
class TableSys;

class Test;

class Ctx : public Singleton<Ctx>
{
protected:
	UIManager* m_uiMgr;
	EngineData* m_engineData;
	EngineApi* m_engineApi;
	INetMgr* m_pINetMgr;
	TableSys* m_pTableSys;
	StdoutLog* m_pStdoutLog;

	Test* m_test;

public:
	Ctx();
	~Ctx();

	void init();
	void setUIMgr(UIManager* uiMgr);
	UIManager* getUIMgr();

	EngineData* getEngineData();
	EngineApi* getEngineApi();
	void setEngineApi(EngineApi* engineApi);
	void setNetMgr(INetMgr* pINetMgr);
	INetMgr* getNetMgr();
	TableSys* getTableSys();

	StdoutLog* getStdLog();
};

#define G_PTABLESYS Ctx::getSingletonPtr()->getTableSys()

#endif				// __CTX_H