#ifndef __TESTEXTERN_H
#define __TESTEXTERN_H

#include "TestStaticLib/TestStaticLibA.h"
#include "TestStaticLib/TestStaticLibB.h"

class TestExtern
{
public:
	TestStaticLibA* m_testStaticLibA;
	TestStaticLibB* m_testStaticLibB;

public:
	TestExtern();
};

#endif				// __TESTEXTERN_H