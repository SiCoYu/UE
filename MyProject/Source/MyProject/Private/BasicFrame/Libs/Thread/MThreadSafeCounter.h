#pragma once

#include "HAL/ThreadSafeCounter.h"	// FThreadSafeCounter

class MThreadSafeCounter
{
protected:
	FThreadSafeCounter mThreadSafeCounter;

public:
	MThreadSafeCounter();
	MThreadSafeCounter(int Value);
	~MThreadSafeCounter();

public:
	int Increment();
	int Add(int Amount);
	int Decrement();
	int Subtract(int Amount);
	int Set(int Value);
	int Reset();
	int GetValue() const;
};