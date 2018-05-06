#include "MyProject.h"
#include "DaoJiShiTimer.h"

void DaoJiShiTimer::OnTimer(float delta)
{
	if (this->mIsDisposed)
	{
		return;
	}

	this->mCurTime -= delta;
	this->mCurLeftTimer += delta;

	if (this->mIsInfineLoop)
	{
		this->checkAndDisp();
	}
	else
	{
		if (this->mCurTime <= 0)
		{
			this->disposeAndDisp();
		}
		else
		{
			this->checkAndDisp();
		}
	}
}

void DaoJiShiTimer::reset()
{
	this->mCurTime = this->mTotalTime;
	this->mCurLeftTimer = 0;
	this->mIsDisposed = false;
}