#include "MyProject.h"
#include "AppFrame.h"
#include "UIManager.h"
#include "Ctx.h"
#include "EngineApi.h"

void AppFrame::initApp()
{
	Ctx::getSingletonPtr()->init();
	Ctx::getSingletonPtr()->setUIMgr(new UIManager());
	Ctx::getSingletonPtr()->setEngineApi(new EngineApi());

	// test
	//Ctx::getSingletonPtr()->getUIMgr()->loadForm(eUIPack);
}
