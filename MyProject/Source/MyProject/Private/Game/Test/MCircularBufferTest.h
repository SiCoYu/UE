#ifndef __CIRCULARBUFFERTEST_H
#define __CIRCULARBUFFERTEST_H

#include "MCircularBuffer.h"
#include "gtest/gtest.h"

class MCircularBufferTest : public testing::Test
{
protected:
	virtual void SetUp() 
	{
		// None yet
	}
	virtual void TearDown() 
	{
		// None yet
	}
	MCircularBuffer m_circularBuffer;

public:
	MCircularBufferTest();
};


#endif				// __CIRCULARBUFFERTEST_H