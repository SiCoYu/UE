#include "MyProject.h"
#include "MyAppFrame.h"
#include "UIManager.h"
#include "MyCtx.h"

void MyAppFrame::initApp()
{
	MyCtx::getSingletonPtr()->initUIMgr(new UIManager());
}
