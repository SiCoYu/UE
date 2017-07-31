#ifndef __TESTSTATICLIBB_H
#define __TESTSTATICLIBB_H

#include <string>
#include "TestStaticLibA.h"

class TestStaticLibB : public TestStaticLibA
{
public:
	virtual int testFunc(std::string bbb);
};


#endif 	// __TESTSTATICLIB_H