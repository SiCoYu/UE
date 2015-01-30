#ifndef __MYCTX_H
#define __MYCTX_H

#include "Singleton.h"
#include "IUIManager.h"

class IUIManager;
class UGameInstance;

class MyCtx : public Singleton<MyCtx>
{
protected:
	IUIManager* m_uiMgr;
	UGameInstance* m_uGameInstance;

public:
	void init();
	void initUIMgr(IUIManager* uiMgr);
	IUIManager* getUIMgr();
	void setGameInstance(UGameInstance* ins);
	UGameInstance* getGameInstance();
};

#endif				// __MYCTX_H