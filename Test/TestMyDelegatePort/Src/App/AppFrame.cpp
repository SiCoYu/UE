#include "AppFrame.h"

namespace MyNS
{
	AppFrame::AppFrame()
	{
		
	}

	AppFrame::~AppFrame()
	{

	}

	void AppFrame::init()
	{
		this->mCommonDelegate.BindRaw(this, &AppFrame::handle);
		this->mCommonDelegate.Execute(10, 10, true);
	}

	void AppFrame::dispose()
	{

	}

	void AppFrame::handle(int aaa, int bbb, bool ccc)
	{

	}
}