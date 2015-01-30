#include "MyProject.h"
#include "MyAppFrame.h"
#include "UIManager.h"
#include "Ctx.h"

void AppFrame::initApp()
{
	Ctx::getSingletonPtr()->init();
	Ctx::getSingletonPtr()->initUIMgr(new UIManager());

	// test
	//Ctx::getSingletonPtr()->getUIMgr()->loadForm(eUIPack);
}
