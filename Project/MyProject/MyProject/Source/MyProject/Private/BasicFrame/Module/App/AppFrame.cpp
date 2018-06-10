#include "MyProject.h"
#include "AppFrame.h"
#include "Prequisites.h"
#include "DataPrequisites.h"
#include "MyMemoryTracker.h"

MY_BEGIN_NAMESPACE(MyNS)

void AppFrame::initApp()
{
	AppFrame::getSingletonPtr()->init();
}

void AppFrame::quitApp()
{
	AppFrame::getSingletonPtr()->dispose();
	AppFrame::deleteSingletonPtr();

	// 最后清理内存追踪
	MyMemoryTracker::get().reportLeaks();
	MyMemoryTracker::get().clear();
}

void AppFrame::init()
{
	CtxExt::setSingletonPtr(MY_NEW CtxExt());
	CtxExt::getSingletonPtr()->construct();
}

void AppFrame::dispose()
{
	CtxExt::getSingletonPtr()->dispose();
	CtxExt::deleteSingletonPtr();
}

MY_END_NAMESPACE