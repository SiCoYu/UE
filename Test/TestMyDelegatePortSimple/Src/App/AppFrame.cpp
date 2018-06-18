#include "AppFrame.h"
#include "MyMiniDelegateDef.h"

namespace MyNS
{
	MY_MINI_DECLARE_DELEGATE_RetVal_TwoParams(bool, AAA, int, char);
	MY_MINI_DECLARE_DELEGATE_OneParam(BBB, char);

	class TestA
	{
	public:
		bool testHandle(int a, char b)
		{
			return false;
		}

		bool testHandleA(int c, int a, char b)
		{
			//MyMiniDelegate<bool, int, char> aaa;
			AAA aaa;
			aaa.bindObjectHandle(&TestA::testHandleB, this, 10);
			bool ret = aaa.call(8, 'a');
			return true;
		}

		bool testHandleB(int c, int a, char b) const
		{
			return true;
		}

		bool testHandleC(int a, char b) const
		{
			return true;
		}

		void testHandleD(int a, char b)
		{
			
		}
	};

	bool testHandle(int a, char b)
	{
		return false;
	}

	void testHandleB(int a, char b)
	{
		
	}

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

		//if (nullptr != this->mCommonDelegate)
		//{
		//
		//}

		//MyMiniDelegate<bool, int, char> aaa;
		AAA aaa;
		aaa.bindStaticHandle(&testHandle);
		bool ret = aaa.call(10, 'a');

		TestA* testA = new TestA();
		aaa.bindObjectHandle(&TestA::testHandle, testA);
		ret = aaa.call(10, 'a');

		aaa.bindObjectHandle(&TestA::testHandleA, testA, 10);
		ret = aaa.call(8, 'a');

		aaa.bindObjectHandle(&TestA::testHandleB, testA, 10);
		ret = aaa.call(8, 'a');

		aaa.bindObjectHandle(&TestA::testHandleC, testA);
		ret = aaa.call(8, 'a');

		MyMiniDelegate<void, int, char> bbb;

		bbb.bindStaticHandle(&testHandleB);
		bbb.call(10, 'a');

		BBB fff;
		fff.bindObjectHandle(&TestA::testHandleD, testA, 6);
		fff.call('a');
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