#include "MyProject.h"
#include "TimerItemBase.h"
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

void addTimerEventHandle(EventDispatchDelegate handle)
{
	if (nullptr == this->mTimerDispatch)
	{
		this->mTimerDispatch = MY_NEW AddOnceEventDispatch();
	}

	this->mTimerDispatch->addEventHandle(handle);
}

void removeTimerEventHandle(EventDispatchDelegate handle)
{
	this->mTimerDispatch->removeEventHandle(handle);
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
		this->checkAndDisp();
	}
	else
	{
		if (this->mCurTime >= this->mTotalTime)
		{
			this->disposeAndDisp();
		}
		else
		{
			this->checkAndDisp();
		}
	}
}

void TimerItemBase::disposeAndDisp()
{
	this->mIsDisposed = true;

	this->mTimerDispatch->dispatchEvent(this);
}

void TimerItemBase::checkAndDisp()
{
	if (this->mCurLeftTimer >= this->mInternal)
	{
		this->mCurLeftTimer = this->mCurLeftTimer - mInternal;

		this->mTimerDispatch->dispatchEvent(this);
	}
}

void TimerItemBase::reset()
{
	this->mCurTime = 0;
	this->mCurLeftTimer = 0;
	this->mIsDisposed = false;
}

void TimerItemBase::setClientDispose()
{

}

bool TimerItemBase::isClientDispose()
{
	return false;
}

MY_END_NAMESPACE