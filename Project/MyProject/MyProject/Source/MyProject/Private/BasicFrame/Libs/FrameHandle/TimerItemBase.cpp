#include "MyProject.h"
#include "TimerItemBase.h"
#include "EventDispatchFunctionObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

TimerItemBase::TimerItemBase()
{
	this->mInternal = 1;
	this->mTotalTime = 1;
	this->mCurTime = 0;
	this->mIsInfineLoop = false;
	this->mCurLeftTimer = 0;
	this->mTimerDispatch = nullptr;
	this->mIsDisposed = false;
}

TimerItemBase::~TimerItemBase()
{

}

void TimerItemBase::init()
{

}

void TimerItemBase::dispose()
{

}

void TimerItemBase::addTimerEventHandle(EventDispatchDelegate handle)
{
	if (nullptr == this->mTimerDispatch)
	{
		this->mTimerDispatch = MY_NEW EventDispatchFunctionObject();
	}

	this->mTimerDispatch->setEventHandle(handle);
}

void TimerItemBase::removeTimerEventHandle(EventDispatchDelegate handle)
{
	this->mTimerDispatch->clearEventHandle();
}

void TimerItemBase::OnTimer(float delta)
{
	if (this->mIsDisposed)
	{
		return;
	}

	this->mCurTime += delta;
	this->mCurLeftTimer += delta;

	if (this->mIsInfineLoop)
	{
		this->checkAndDispatch();
	}
	else
	{
		if (this->mCurTime >= this->mTotalTime)
		{
			this->disposeAndDispatch();
		}
		else
		{
			this->checkAndDispatch();
		}
	}
}

void TimerItemBase::disposeAndDispatch()
{
	this->mIsDisposed = true;

	this->mTimerDispatch->call(this);
}

void TimerItemBase::checkAndDispatch()
{
	if (this->mCurLeftTimer >= this->mInternal)
	{
		this->mCurLeftTimer = this->mCurLeftTimer - mInternal;

		this->mTimerDispatch->call(this);
	}
}

void TimerItemBase::reset()
{
	this->mCurTime = 0;
	this->mCurLeftTimer = 0;
	this->mIsDisposed = false;
}

MY_END_NAMESPACE