#include "MyProject.h"
#include "FrameInterval.h"

MY_BEGIN_NAMESPACE(MyNS)

FrameInterval::FrameInterval()
{
	this->mInterval = 1;
	this->mTotalFrame = 0;
	this->mCurFrame = 0;
}

void FrameInterval::setInterval(int value)
{
	this->mInterval = value;
}

void FrameInterval::setTotalFrame(int value)
{
	this->mTotalFrame = value;
}

void FrameInterval::setCurFrame(int value)
{
	this->mCurFrame = value;
}

bool FrameInterval::canExec(int delta)
{
	bool ret = false;

	this->mTotalFrame += delta;
	this->mCurFrame += delta;

	if (this->mCurFrame >= this->mInterval)
	{
		ret = true;
		this->mCurFrame -= this->mInterval;
	}

	return ret;
}

MY_END_NAMESPACE