#ifndef __TestLuaBind_H
#define __TestLuaBind_H

#include "TestBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @url https://segmentfault.com/a/1190000005765697
 */
class TestLuaBind : public TestBase
{
public:
	virtual void run() override;
};

MY_END_NAMESPACE

#endif