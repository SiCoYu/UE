#ifndef __TestMemory_H
#define __TestMemory_H

#include "TestBase.h"

class TestMemoryObject;

class TestMemory : public TestBase
{
protected:
	TestMemoryObject* mTestMemoryObject;

public:
	virtual void run() override;
};

#endif