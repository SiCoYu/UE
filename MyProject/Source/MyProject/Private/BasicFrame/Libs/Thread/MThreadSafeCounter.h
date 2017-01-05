#pragma once

#include "HAL/ThreadSafeCounter.h"	// FThreadSafeCounter

class MThreadSafeCounter
{
protected:
	FThreadSafeCounter mThreadSafeCounter;
};