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

		// 类模板中模板构造函数调用这样调用会报错，需要如下 this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(this, &AppFrame::handle); 调用才行
		//this->mCommonDelegate = MyCommonDelegate(this, &AppFrame::handle);
		//this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(this, &AppFrame::handle);
		//this->mCommonDelegate = MakeMemFunDelegate(this, &AppFrame::handle);
		//MyCommonDelegate().BindRaw(this, &AppFrame::handle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate = MyCommonDelegate(&MyNS::handle);
		//this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(0, &MyNS::handle);
		//this->mCommonDelegate = MakeStaticFunDelegate(&MyNS::handle);
		//MyCommonDelegate().BindStatic(&MyNS::handle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate.BindStatic(&MyNS::staticHandle);
		//MyCommonDelegate().BindStatic(&MyNS::staticHandle);
		//this->mCommonDelegate.Execute(10, 10, true);

		//this->mCommonDelegate = MySmBaseDelegate<int, int, bool>::MySmBaseDelegate(10);

		if (nullptr != this->mCommonDelegate)
		{

		}
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