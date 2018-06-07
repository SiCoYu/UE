#include "MyProject.h"
#include "Prequisites.h"
#include "AppFrame.h"

void AppFrame::initApp()
{
	GCtx->construct();
}

void AppFrame::quitApp()
{
	GCtx->deleteSingletonPtr();
}
