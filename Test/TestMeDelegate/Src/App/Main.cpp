#include "MyMiniDelegateBase.h"
#include "MyMiniDelegate.h"
#include "MyMiniDelegateInstanceBase.h"
#include "MyMiniDelegateInstanceImpl.h"

using namespace MyNS;

class TestA
{
public:
	bool testHandle(int a, char b)
	{
		return false;
	}
};

bool testHandle(int a, char b)
{
	return false;
}

void main()
{
	MyMiniDelegateBase* aaa = new MyMiniDelegate<bool, int, char>();
}