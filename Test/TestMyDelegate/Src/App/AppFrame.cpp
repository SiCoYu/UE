#include "AppFrame.h"

namespace MyNS
{
	AppFrame::AppFrame()
	{
		mCommonDelegate.BindRaw(this, &AppFrame::handle);
		mCommonDelegate.Execute(10, 10, true);
	}

	AppFrame::~AppFrame()
	{

	}

	void AppFrame::handle(int aaa, int bbb, bool ccc)
	{

	}
}