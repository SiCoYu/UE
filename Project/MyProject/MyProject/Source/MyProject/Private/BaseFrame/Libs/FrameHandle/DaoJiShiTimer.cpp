#include "MyProject.h"
#include "DaoJiShiTimer.h"

MY_BEGIN_NAMESPACE(MyNS)

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
		this->checkAndDispatch();
	}
	else
	{
		if (this->mCurTime <= 0)
		{
			this->disposeAndDispatch();
		}
		else
		{
			this->checkAndDispatch();
		}
	}
}

void DaoJiShiTimer::reset()
{
	this->mCurTime = this->mTotalTime;
	this->mCurLeftTimer = 0;
	this->mIsDisposed = false;
}

MY_END_NAMESPACE