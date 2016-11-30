#ifndef __GLOBALEVENT_H
#define __GLOBALEVENT_H

#include "gtest/gtest.h"

class GrobalEvent : public testing::Environment
{
public:
	virtual void SetUp();
	virtual void TearDown();
};

#endif				// __GLOBALEVENT_H