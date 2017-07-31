#include "MyProject.h"
#include "TimerItemBase.h"

TimerItemBase::TimerItemBase()
{
	mInternal = 1;
	mTotalTime = 1;
	mCurTime = 0;
	mIsInfineLoop = false;
	mCurLeftTimer = 0;
	mTimerDisp = nullptr;
	mIsDisposed = false;
}

void TimerItemBase::OnTimer(float delta)
{
	if (mIsDisposed)
	{
		return;
	}

	mCurTime += delta;
	mCurLeftTimer += delta;

	if (mIsInfineLoop)
	{
		checkAndDisp();
	}
	else
	{
		if (mCurTime >= mTotalTime)
		{
			disposeAndDisp();
		}
		else
		{
			checkAndDisp();
		}
	}
}

void TimerItemBase::disposeAndDisp()
{
	mIsDisposed = true;
	if (!mTimerDisp.empty())
	{
		mTimerDisp(this);
	}
}

void TimerItemBase::checkAndDisp()
{
	if (mCurLeftTimer >= mInternal)
	{
		mCurLeftTimer = mCurLeftTimer - mInternal;

		if (!mTimerDisp.empty())
		{
			mTimerDisp(this);
		}
	}
}

void TimerItemBase::reset()
{
	mCurTime = 0;
	mCurLeftTimer = 0;
	mIsDisposed = false;
}

void TimerItemBase::setClientDispose()
{

}

bool TimerItemBase::isClientDispose()
{
	return false;
}