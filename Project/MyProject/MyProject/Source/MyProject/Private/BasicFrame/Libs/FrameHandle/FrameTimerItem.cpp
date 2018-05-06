#include "MyProject.h"
#include "FrameTimerItem.h"

FrameTimerItem::FrameTimerItem()
{
	this->mInternal = 1;
	this->mTotalFrameCount = 1;
	this->mCurFrame = 0;
	this->mCurLeftFrame = 0;
	this->mIsInfineLoop = false;
	this->mTimerDispatch = nullptr;
	this->mIsDisposed = false;
}

void FrameTimerItem::OnFrameTimer()
{
	if (this->mIsDisposed)
	{
		return;
	}

	++this->mCurFrame;
	++this->mCurLeftFrame;

	if (this->mIsInfineLoop)
	{
		if (this->mCurLeftFrame == mInternal)
		{
			this->mCurLeftFrame = 0;

			if (!mTimerDispatch.empty())
			{
				this->mTimerDispatch(this);
			}
		}
	}
	else
	{
		if (this->mCurFrame == this->mTotalFrameCount)
		{
			this->mIsDisposed = true;

			if (!this->mTimerDispatch.empty())
			{
				this->mTimerDispatch(this);
			}
		}
		else
		{
			if (this->mCurLeftFrame == this->mInternal)
			{
				this->mCurLeftFrame = 0;

				if (!this->mTimerDispatch.empty())
				{
					this->mTimerDispatch(this);
				}
			}
		}
	}
}

void FrameTimerItem::reset()
{
	this->mCurFrame = 0;
	this->mCurLeftFrame = 0;
	this->mIsDisposed = false;
}

void FrameTimerItem::setClientDispose()
{

}

bool FrameTimerItem::isClientDispose()
{
	return false;
}