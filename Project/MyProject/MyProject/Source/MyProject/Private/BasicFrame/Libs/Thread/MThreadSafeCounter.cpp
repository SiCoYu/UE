#include "MyProject.h"
#include "MThreadSafeCounter.h"

MThreadSafeCounter::MThreadSafeCounter()
	: mThreadSafeCounter()
{

}

MThreadSafeCounter::MThreadSafeCounter(int Value)
	: mThreadSafeCounter(Value)
{

}

MThreadSafeCounter::~MThreadSafeCounter()
{

}

int MThreadSafeCounter::Increment()
{
	return mThreadSafeCounter.Increment();
}

int MThreadSafeCounter::Add(int32 Amount)
{
	return mThreadSafeCounter.Add(Amount);
}

int MThreadSafeCounter::Decrement()
{
	return mThreadSafeCounter.Decrement();
}

int MThreadSafeCounter::Subtract(int Amount)
{
	return mThreadSafeCounter.Subtract(Amount);
}

int MThreadSafeCounter::Set(int Value)
{
	return mThreadSafeCounter.Set(Value);
}

int MThreadSafeCounter::Reset()
{
	return mThreadSafeCounter.Reset();
}

int MThreadSafeCounter::GetValue() const
{
	return mThreadSafeCounter.GetValue();
}