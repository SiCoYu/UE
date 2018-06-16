#include "MyProject.h"
#include "SystemTimeData.h"
#include "UtilEngineWrap.h"

MY_BEGIN_NAMESPACE(MyNS)

SystemTimeData::SystemTimeData()
{
	this->mPreTime = 0;
	this->mCurTime = 0;
	this->mDeltaSec = 0.0f;

	this->mIsFixFrameRate = false;
	this->mFixFrameRate = 0.0417f;       //  1 / 24;
	this->mScale = 1;

	this->mFixedTimestep = 0.02f;
}

void SystemTimeData::init()
{

}

void SystemTimeData::dispose()
{

}

float SystemTimeData::getDeltaSec()
{
	return this->mDeltaSec;
}

void SystemTimeData::setDeltaSec(float value)
{
	this->mDeltaSec = value;
}

long SystemTimeData::getCurTime()
{
	return this->mCurTime;
}

void SystemTimeData::setCurTime(long value)
{
	this->mCurTime = value;
}

float SystemTimeData::getFixedTimestep()
{
	return this.mDeltaSec;
}

// 获取固定帧率时间间隔
float SystemTimeData::getFixFrameRateInterval()
{
	return this.mFixFrameRate;
}

void SystemTimeData::nextFrame()
{
	this->mPreTime = this->mCurTime;
	this->mCurTime = UtilEngineWrap::getUTCSec();

	if (this->mIsFixFrameRate)
	{
		this->mDeltaSec = this->mFixFrameRate;        // 每秒 24 帧
	}
	else
	{
		if (this->mPreTime != 0.0f)     // 第一帧跳过，因为这一帧不好计算间隔
		{
			this->mDeltaSec = this->mCurTime - this->mPreTime;
		}
		else
		{
			this->mDeltaSec = this->mFixFrameRate;        // 每秒 24 帧
		}
	}

	this.mDeltaSec *= this.mScale;
}

MY_END_NAMESPACE