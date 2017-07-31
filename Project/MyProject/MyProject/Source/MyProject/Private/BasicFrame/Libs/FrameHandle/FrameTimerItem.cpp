#include "MyProject.h"
#include "FrameTimerItem.h"

FrameTimerItem::FrameTimerItem()
{
	mInternal = 1;
	mTotalFrameCount = 1;
	mCurFrame = 0;
	mCurLeftFrame = 0;
	mIsInfineLoop = false;
	mTimerDisp = nullptr;
	mIsDisposed = false;
}

void FrameTimerItem::OnFrameTimer()
{
	if (mIsDisposed)
	{
		return;
	}

	++mCurFrame;
	++mCurLeftFrame;

	//if (m_preFrame == mCurFrame)
	//{
	//    Ctx.m_instance.m_logSys.log("aaaaaaaafadfsasdf");
	//}

	//mCurFrame = m_preFrame;

	if (mIsInfineLoop)
	{
		if (mCurLeftFrame == mInternal)
		{
			mCurLeftFrame = 0;

			if (!mTimerDisp.empty())
			{
				mTimerDisp(this);
			}
		}
	}
	else
	{
		if (mCurFrame == mTotalFrameCount)
		{
			mIsDisposed = true;
			if (!mTimerDisp.empty())
			{
				mTimerDisp(this);
			}
		}
		else
		{
			if (mCurLeftFrame == mInternal)
			{
				mCurLeftFrame = 0;
				if (!mTimerDisp.empty())
				{
					mTimerDisp(this);
				}
			}
		}
	}
}

void FrameTimerItem::reset()
{
	mCurFrame = 0;
	mCurLeftFrame = 0;
	mIsDisposed = false;
}

void FrameTimerItem::setClientDispose()
{

}

bool FrameTimerItem::isClientDispose()
{
	return false;
}