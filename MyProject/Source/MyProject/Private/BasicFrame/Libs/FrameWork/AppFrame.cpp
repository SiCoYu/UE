#include "MyProject.h"
#include "AppFrame.h"
#include "Common.h"

void AppFrame::initApp()
{
	GCtx->init();
	//GCtx->setUiMgr(new UIManager());
	//GCtx->setEngineApi(new EngineApi());
	//GCtx->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

	// test
	//GUiMgr->loadForm(eUIPack);
	GNetMgr->openSocket("192.168.124.26", 10002);
}
