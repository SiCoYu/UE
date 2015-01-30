#include "MyProject.h"
#include "MyAppFrame.h"
#include "UIManager.h"
#include "MyCtx.h"

void MyAppFrame::initApp()
{
	MyCtx::getSingletonPtr()->init();
	MyCtx::getSingletonPtr()->initUIMgr(new UIManager());

	// test
	//MyCtx::getSingletonPtr()->getUIMgr()->loadForm(eUIPack);
}
