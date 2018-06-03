#include "MyProject.h"
#include "TimeInterval.h"

MY_BEGIN_NAMESPACE(MyNS)

TimeInterval::TimeInterval()
{
	this->mInterval = 1 / 10;    // 每一秒更新 10 次
	this->mTotalTime = 0;
	this->mCurTime = 0;

	this->mTotalExecNum = 0;     // 如果是 0 ，就说明没有限制
	this->mCurExecNum = 0;
}

void TimeInterval::setInterval(float value)
{
	this->mInterval = value;
}

void TimeInterval::setTotalTime(float value)
{
	this->mTotalTime = value;
}

void TimeInterval::setCurTime(float value)
{
	this->mCurTime = value;
}

void TimeInterval::setTotalExecNum(int value)
{
	this->mTotalExecNum = value;
}

void TimeInterval::setCurExecNum(int value)
{
	this->mCurExecNum = value;
}

// 当前是否满足间隔条件
bool TimeInterval::canExec(float delta)
{
	bool ret = false;

	this->mTotalTime += delta;
	this->mCurTime += delta;

	if (this->mCurTime >= this->mInterval)
	{
		if (0 == this->mTotalExecNum ||
			this->mCurExecNum < this->mTotalExecNum)
		{
			this->mCurTime -= this->mInterval;
			ret = true;
		}
		else
		{
			ret = false;
		}

		this->mCurExecNum += 1;
	}

	return ret;
}

// 是否执行结束
bool TimeInterval::isExecEnd()
{
	bool ret = false;

	if (0 != this->mTotalExecNum &&
		this->mCurExecNum >= this->mTotalExecNum)
	{
		ret = true;
	}

	return ret;
}

MY_END_NAMESPACE