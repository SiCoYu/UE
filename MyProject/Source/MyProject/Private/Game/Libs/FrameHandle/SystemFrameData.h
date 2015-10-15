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

    void nextFrame(float delta)
    {
        ++m_totalFrameCount;
        ++m_curFrameCount;
        m_curTime += delta;

        if(m_curTime > 1.0f)
        {
            m_fps = (int)(m_curFrameCount / m_curTime);
            m_curFrameCount = 0;
            m_curTime = 0;

            //Ctx.m_instance.m_logSys.log(string.Format("当前帧率 {0}", m_fps));
        }
    }
};

#endif