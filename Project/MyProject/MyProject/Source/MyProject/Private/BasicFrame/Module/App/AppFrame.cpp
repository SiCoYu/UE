#include "MyProject.h"
#include "AppFrame.h"
#include "Prequisites.h"
#include "DataPrequisites.h"
#include "MyMemoryTracker.h"

MY_BEGIN_NAMESPACE(MyNS)

void AppFrame::initApp()
{
	CtxExt::setSingletonPtr(MY_NEW CtxExt());
	GCtxExt->construct();
}

void AppFrame::quitApp()
{
	GCtxExt->dispose();
	GCtxExt->deleteSingletonPtr();

	// 最后清理内存追踪
	MyMemoryTracker::get().reportLeaks();
	MyMemoryTracker::get().clear();
}

MY_END_NAMESPACE