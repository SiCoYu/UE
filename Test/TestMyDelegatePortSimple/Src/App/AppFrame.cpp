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
		//this->mCommonDelegate.BindRaw(this, &AppFrame::handle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate.BindStatic(&MyNS::handle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate.BindStatic(&MyNS::staticHandle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate = MyCommonDelegate(this, &AppFrame::handle);
		this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(this, &AppFrame::handle);
		//MyCommonDelegate().BindRaw(this, &AppFrame::handle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate = MyCommonDelegate(&MyNS::handle);
		//this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(&MyNS::handle);
		//MyCommonDelegate().BindStatic(&MyNS::handle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate.BindStatic(&MyNS::staticHandle);
		//MyCommonDelegate().BindStatic(&MyNS::staticHandle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate = MySmBaseDelegate<int, int, bool>::MySmBaseDelegate(10);
	}

	void AppFrame::dispose()
	{

	}

	void AppFrame::handle(int aaa, int bbb, bool ccc)
	{

	}

	void handle(int aaa, int bbb, bool ccc)
	{

	}

	void staticHandle(int aaa, int bbb, bool ccc)
	{

	}
}