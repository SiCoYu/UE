#ifndef __SystemFrameData_H
#define __SystemFrameData_H

#include "Platform.h"

class SystemFrameData
{
protected:
	uint32 m_totalFrameCount;       // 当前帧数
    uint32 m_curFrameCount;         // 当前帧数
    float m_curTime;          // 当前一秒内时间
    int m_fps;                // 帧率

	void nextFrame(float delta);
};

#endif