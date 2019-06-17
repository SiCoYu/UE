#pragma once

#include "HAL/ThreadSafeCounter.h"	// FThreadSafeCounter
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MThreadSafeCounter
{
protected:
	FThreadSafeCounter mThreadSafeCounter;

public:
	MThreadSafeCounter();
	MThreadSafeCounter(int Value);
	~MThreadSafeCounter();

public:
	void init();
	void dispose();

	int Increment();
	int Add(int Amount);
	int Decrement();
	int Subtract(int Amount);
	int Set(int Value);
	int Reset();
	int GetValue() const;
};

MY_END_NAMESPACE