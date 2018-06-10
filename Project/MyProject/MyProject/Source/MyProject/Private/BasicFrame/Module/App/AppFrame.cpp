#include "MyProject.h"
#include "AppFrame.h"
#include "Prequisites.h"
#include "DataPrequisites.h"
#include "MyMemoryTracker.h"

MY_BEGIN_NAMESPACE(MyNS)

AppFrame* AppFrame::msAppFrame = nullptr;

void AppFrame::initApp()
{
	AppFrame::msAppFrame = MY_NEW AppFrame();
	AppFrame::mAppFrame->init();
}

void AppFrame::quitApp()
{
	AppFrame::mAppFrame->dispose();
	MY_DELETE AppFrame::mAppFrame;
	AppFrame::mAppFrame = nullptr;

	// 最后清理内存追踪
	MyMemoryTracker::get().reportLeaks();
	MyMemoryTracker::get().clear();
}

void AppFrame::init()
{
	CtxExt::setSingletonPtr(MY_NEW CtxExt());
	GCtxExt->construct();
}

void AppFrame::dispose()
{
	GCtxExt->dispose();
	GCtxExt->deleteSingletonPtr();
}

MY_END_NAMESPACE