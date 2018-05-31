#ifndef __TestNetClientBuffer_H
#define __TestNetClientBuffer_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

#include "MCircularBuffer.h"
//#include "gtest/gtest.h"

//class MCircularBufferTest : public testing::Test
class MCircularBufferTest
{
protected:
	MCircularBuffer mCircularBuffer;

protected:
	static void SetUpTestCase();
	static void TearDownTestCase();

	virtual void SetUp();
	virtual void TearDown();

public:
	MCircularBufferTest();
	virtual ~MCircularBufferTest();
};

MY_END_NAMESPACE

#endif				// __TestNetClientBuffer_H