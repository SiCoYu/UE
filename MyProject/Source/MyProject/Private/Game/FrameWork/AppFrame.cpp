#include "MyProject.h"
#include "AppFrame.h"
#include "Common.h"

void AppFrame::initApp()
{
	g_pCtx->init();
	//g_pCtx->setUIMgr(new UIManager());
	//g_pCtx->setEngineApi(new EngineApi());
	//g_pCtx->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

	// test
	//g_pUIMgr->loadForm(eUIPack);
	g_pNetMgr->openSocket("192.168.124.26", 10002);
}
