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
	MyMiniDelegate<bool, int, char>* aaa = new MyMiniDelegate<bool, int, char>();
	aaa->bindStaticHandle(&testHandle);
	bool ret = aaa->call(10, 'a');
}