#include "MyProject.h"
#include "SystemFrameData.h"

void SystemFrameData::nextFrame(float delta)
{
	++mTotalFrameCount;
	++mCurFrameCount;
	mCurTime += delta;

	if (mCurTime > 1.0f)
	{
		mFps = (int)(mCurFrameCount / mCurTime);
		mCurFrameCount = 0;
		mCurTime = 0;

		//Ctx.m_instance.m_logSys.log(string.Format("当前帧率 {0}", mFps));
	}
}