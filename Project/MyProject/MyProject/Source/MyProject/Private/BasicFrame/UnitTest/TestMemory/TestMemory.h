#ifndef __TestMemory_H
#define __TestMemory_H

#include "TestBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestMemoryObject;

class TestMemory : public TestBase
{
protected:
	TestMemoryObject* mTestMemoryObject;

public:
	virtual void run() override;
};

MY_END_NAMESPACE

#endif