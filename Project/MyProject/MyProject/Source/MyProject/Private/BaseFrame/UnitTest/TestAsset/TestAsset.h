#pragma once

#include "TestBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestAsset : public TestBase
{
public:
	virtual void run() override;

protected:
	void _testDep();
	void _testGetAssetData();
};

MY_END_NAMESPACE