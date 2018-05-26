#ifndef __TestExtern_H
#define __TestExtern_H

#include "TestStaticLib/TestStaticLibA.h"
#include "TestStaticLib/TestStaticLibB.h"
#include "GObject.h"

class TestExtern : public GObject 
{
public:
	TestStaticLibA* mTestStaticLibA;
	TestStaticLibB* mTestStaticLibB;

public:
	TestExtern();
};

#endif				// __TESTEXTERN_H