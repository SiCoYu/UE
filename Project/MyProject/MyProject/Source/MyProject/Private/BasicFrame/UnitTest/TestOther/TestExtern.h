#ifndef __TestExtern_H
#define __TestExtern_H

#include "TestStaticLib/TestStaticLibA.h"
#include "TestStaticLib/TestStaticLibB.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_USING_NAMESPACE(MyNS)

class TestExtern : public TestBase
{
public:
	TestStaticLibA* mTestStaticLibA;
	TestStaticLibB* mTestStaticLibB;

public:
	TestExtern();
};

#endif				// __TestExtern_H