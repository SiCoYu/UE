#include "MyProject.h"
#include "AppFrame.h"
#include "Prequisites.h"
#include "DataPrequisites.h"

void AppFrame::initApp()
{
	CtxExt::setSingletonPtr(MY_NEW CtxExt());
	GCtxExt->construct();
}

void AppFrame::quitApp()
{
	GCtxExt->dispose();
	GCtxExt->deleteSingletonPtr();
}