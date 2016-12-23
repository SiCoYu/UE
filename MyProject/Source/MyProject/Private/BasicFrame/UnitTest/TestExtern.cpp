#include "MyProject.h"
#include "TestExtern.h"
#include "Templates/Casts.h"

#define dynamic_cast aaa

TestExtern::TestExtern()
{
	//mTestStaticLibB = new TestStaticLibB();
	//mTestStaticLibB->testFunc("aaaaaaa");

	//mTestStaticLibA = dynamic_cast<TestStaticLibA*>(mTestStaticLibB);
	//mTestStaticLibA->testFunc("aaaaaaa");

	mTestStaticLibA = new TestStaticLibB();
	mTestStaticLibA->testFunc("aaaaaaa");

	mTestStaticLibB = (TestStaticLibB*)mTestStaticLibA;
	mTestStaticLibA->testFunc("aaaaaaa");
}
