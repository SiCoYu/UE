#ifndef __MYCTX_H
#define __MYCTX_H

#include "Singleton.h"

class MyCtx : public Singleton<MyCtx>
{
protected:
	IUIManager* m_uiMgr;

public:
	void initUIMgr(IUIManager* uiMgr);
};

#endif				// __MYCTX_H