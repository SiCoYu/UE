#include "MyProject.h"
#include "SystemTimeData.h"
#include "EngineApi.h"

SystemTimeData::SystemTimeData()
{
	mPreTime = 0;
	mCurTime = 0;
	mDeltaSec = 0.0f;
}

float SystemTimeData::getDeltaSec()
{
	return mDeltaSec;
}

void SystemTimeData::setDeltaSec(float value)
{
	mDeltaSec = value;
}

long SystemTimeData::getCurTime()
{
	return mCurTime;
}
void SystemTimeData::setCurTime(long value)
{
	mCurTime = value;
}

void SystemTimeData::nextFrame()
{
	mCurTime = EngineApi::getUTCSec();
	if (mPreTime != 0.0f)     // 第一帧跳过，因为这一帧不好计算间隔
	{
		mDeltaSec = mCurTime - mPreTime;
	}
	else
	{
		mDeltaSec = 1 / 24;        // 每秒 24 帧
	}
	mPreTime = mCurTime;
}