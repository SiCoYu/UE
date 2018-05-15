#pragma once

#include "MySmDelegateCombinations.h"

// �����巵�����͵�ʱ�� this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(this, &AppFrame::handle); ����д�ᱨ��
MY_DECLARE_DELEGATE_ThreeParams(MyCommonDelegate, int, int, bool);
//MY_DECLARE_DELEGATE_RetVal_ThreeParams(void, MyCommonDelegate, int, int, bool);

namespace MyNS
{
	class AppFrame
	{
	protected:
		// ʹ�ú궨���ʱ�� this->mCommonDelegate = MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(this, &AppFrame::handle); ����д�ᱨ��
		//MyCommonDelegate mCommonDelegate;
		//MySmBaseDelegate<int, int, bool> mCommonDelegate;
		MySmBaseDelegate<void, int, int, bool> mCommonDelegate;

	public:
		AppFrame();
		~AppFrame();

		void init();
		void dispose();

		void handle(int aaa, int bbb, bool ccc);
	};

	void handle(int aaa, int bbb, bool ccc);
	static void staticHandle(int aaa, int bbb, bool ccc);
}