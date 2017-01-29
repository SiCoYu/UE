#include "MyProject.h"
#include "SystemFrameData.h"

SystemFrameData::SystemFrameData()
{

}

uint32 SystemFrameData::getTotalFrameCount()
{
	return this->mTotalFrameCount;
}

void SystemFrameData::nextFrame(float delta)
{
	++this->mTotalFrameCount;
	++this->mCurFrameCount;
	this->mCurTime += delta;

	if (this->mCurTime > 1.0f)
	{
		this->mFps = (int)(this->mCurFrameCount / this->mCurTime);
		this->mCurFrameCount = 0;
		this->mCurTime = 0;

		//Ctx.m_instance.m_logSys.log(string.Format("当前帧率 {0}", mFps));
	}
}

void SystemFrameData::init()
{

}

void SystemFrameData::dispose()
{

}