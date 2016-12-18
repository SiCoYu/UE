#include "MyProject.h"
#include "DaoJiShiTimer.h"

void DaoJiShiTimer::OnTimer(float delta)
{
	if (mIsDisposed)
	{
		return;
	}

	mCurTime -= delta;
	mCurLeftTimer += delta;

	if (mIsInfineLoop)
	{
		checkAndDisp();
	}
	else
	{
		if (mCurTime <= 0)
		{
			disposeAndDisp();
		}
		else
		{
			checkAndDisp();
		}
	}
}

void DaoJiShiTimer::reset()
{
	mCurTime = mTotalTime;
	mCurLeftTimer = 0;
	mIsDisposed = false;
}