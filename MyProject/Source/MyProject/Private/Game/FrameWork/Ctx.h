#ifndef __CTX_H
#define __CTX_H

#include "Singleton.h"
#include "IUIManager.h"

class IUIManager;
class UGameInstance;

class Ctx : public Singleton<Ctx>
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

#endif				// __CTX_H