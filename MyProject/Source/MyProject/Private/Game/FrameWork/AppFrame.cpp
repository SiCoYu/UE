#include "MyProject.h"
#include "AppFrame.h"
#include "UIManager.h"
#include "Ctx.h"
#include "EngineApi.h"
#include "NetMgr.h"

void AppFrame::initApp()
{
	Ctx::getSingletonPtr()->init();
	Ctx::getSingletonPtr()->setUIMgr(new UIManager());
	Ctx::getSingletonPtr()->setEngineApi(new EngineApi());
	Ctx::getSingletonPtr()->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

	// test
	//Ctx::getSingletonPtr()->getUIMgr()->loadForm(eUIPack);
	Ctx::getSingletonPtr()->getNetMgr()->openSocket("192.168.0.101", 10002);
}
