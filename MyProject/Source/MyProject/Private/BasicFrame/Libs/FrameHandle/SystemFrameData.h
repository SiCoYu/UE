#ifndef __SystemFrameData_H
#define __SystemFrameData_H

#include "Platform.h"

class SystemFrameData
{
protected:
	uint32 mTotalFrameCount;       // 当前帧数
    uint32 mCurFrameCount;         // 当前帧数
    float mCurTime;          // 当前一秒内时间
    int mFps;                // 帧率

	void nextFrame(float delta);
};

#endif