#include "MyProject.h"
#include "Common.h"
#include "AppFrame.h"

void AppFrame::initApp()
{
	GCtx->construct();
}

void AppFrame::quitApp()
{
	GCtx->deleteSingletonPtr();
}
