#ifndef __TestUi_H
#define __TestUi_H

#include "TestBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestUi : public TestBase
{
public:
	virtual void run() override;
};

MY_END_NAMESPACE

#endif