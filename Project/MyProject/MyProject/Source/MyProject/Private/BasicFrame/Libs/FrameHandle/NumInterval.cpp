#include "MyProject.h"
#include "NumInterval.h"

MY_BEGIN_NAMESPACE(MyNS)

NumInterval::NumInterval()
{
	this->mTotalValue = 0;
	this->mCurValue = 0;

	this->mNumIntervalMode = NumIntervalMode.eNIM_Inc;
}

void NumInterval::setTotalValue(float value)
{
	this->mTotalValue = value;
}

void NumInterval::setCurValue(float value)
{
	this->mCurValue = value;
}

void NumInterval::reset()
{
	if (NumIntervalMode.eNIM_Inc == this->mNumIntervalMode)
	{
		this->mCurValue = 0;
	}
	else
	{
		this->mCurValue = this->mTotalValue;
	}
}

bool NumInterval::canExec(float delta)
{
	bool ret = false;

	if (NumIntervalMode.eNIM_Inc == this->mNumIntervalMode)
	{
		this->mCurValue += delta;

		if (this->mCurValue <= this->mTotalValue)
		{
			ret = true;
		}
	}
	else
	{
		this->mCurValue -= delta;

		if (this->mCurValue >= 0)
		{
			ret = true;
		}
	}

	return ret;
}

MY_END_NAMESPACE