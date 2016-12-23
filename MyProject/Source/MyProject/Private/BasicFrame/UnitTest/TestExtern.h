#ifndef __TestExtern_H
#define __TestExtern_H

#include "TestStaticLib/TestStaticLibA.h"
#include "TestStaticLib/TestStaticLibB.h"

class TestExtern
{
public:
	TestStaticLibA* mTestStaticLibA;
	TestStaticLibB* mTestStaticLibB;

public:
	TestExtern();
};

#endif				// __TESTEXTERN_H