#ifndef __FrameTimerItem_H
#define __FrameTimerItem_H

#include "IDelayHandleItem.h"

/**
 * @brief 定时器，这个是不断增长的
 */
class FrameTimerItem : public IDelayHandleItem
{
public:
	int m_internal;              // 帧数间隔
    int m_totalFrameCount;       // 总共次数
    int m_curFrame;              // 当前已经调用的定时器的时间
    int m_curLeftFrame;          // 剩余帧数
    bool m_bInfineLoop;      // 是否是无限循环
    Action<FrameTimerItem> m_timerDisp;       // 定时器分发
    bool m_disposed;             // 是否已经被释放

    //int m_preFrame = 0;

	public FrameTimerItem()
	{
		m_internal = 1;
		m_totalFrameCount = 1;
		m_curFrame = 0;
		m_curLeftFrame = 0;
		m_bInfineLoop = false;
		m_timerDisp = nullptr;
		m_disposed = false;
	}

    public virtual void OnFrameTimer()
    {
        if (m_disposed)
        {
            return;
        }

        ++m_curFrame;
        ++m_curLeftFrame;

        //if (m_preFrame == m_curFrame)
        //{
        //    Ctx.m_instance.m_logSys.log("aaaaaaaafadfsasdf");
        //}

        //m_curFrame = m_preFrame;

        if (m_bInfineLoop)
        {
            if (m_curLeftFrame == m_internal)
            {
                m_curLeftFrame = 0;

                if (m_timerDisp != null)
                {
                    m_timerDisp(this);
                }
            }
        }
        else
        {
            if (m_curFrame == m_totalFrameCount)
            {
                m_disposed = true;
                if (m_timerDisp != null)
                {
                    m_timerDisp(this);
                }
            }
            else
            {
                if (m_curLeftFrame == m_internal)
                {
                    m_curLeftFrame = 0;
                    if (m_timerDisp != null)
                    {
                        m_timerDisp(this);
                    }
                }
            }
        }
    }

    public virtual void reset()
    {
        m_curFrame = 0;
        m_curLeftFrame = 0;
        m_disposed = false;
    }

    public void setClientDispose()
    {

    }

    public bool getClientDispose()
    {
        return false;
    }
};

#endif