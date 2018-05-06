#include "MyProject.h"
#include "TestExtern.h"
#include "Templates/Casts.h"

// UE 4.19.1 warning C4005 : 'dynamic_cast' : macro redefinition , engine\source\runtime\coreuobject\public\Templates / Casts.h(417) : note: see previous definition of 'dynamic_cast'
//#define dynamic_cast aaa

TestExtern::TestExtern()
{
	//mTestStaticLibB = new TestStaticLibB();
	//mTestStaticLibB->testFunc("aaaaaaa");

	//mTestStaticLibA = dynamic_cast<TestStaticLibA*>(mTestStaticLibB);
	//mTestStaticLibA->testFunc("aaaaaaa");

	this->mTestStaticLibA = new TestStaticLibB();
	this->mTestStaticLibA->testFunc("aaaaaaa");

	this->mTestStaticLibB = (TestStaticLibB*)mTestStaticLibA;
	this->mTestStaticLibA->testFunc("aaaaaaa");
}
