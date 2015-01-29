#ifndef __MYCTX_H
#define __MYCTX_H

#include "Singleton.h"

class IUIManager;

class MyCtx : public Singleton<MyCtx>
{
protected:
	IUIManager* m_uiMgr;

public:
	void init();
	void initUIMgr(IUIManager* uiMgr);
	IUIManager* getUIMgr();
};

#endif				// __MYCTX_H