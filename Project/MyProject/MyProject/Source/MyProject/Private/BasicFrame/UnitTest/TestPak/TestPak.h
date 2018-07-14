#pragma once

#include "TestBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestPak : public TestBase
{
public:
	virtual void run() override;

protected:
	void _testA();
	void _testB();
	void _testC();
};

MY_END_NAMESPACE