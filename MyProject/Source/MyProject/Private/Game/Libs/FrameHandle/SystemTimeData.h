#ifndef __SystemTimeData_H
#define __SystemTimeData_H

class SystemTimeData
{
protected:
	long m_preTime;           // 上一次更新时的秒数
    long m_curTime;           // 正在获取的时间
    float m_deltaSec;         // 两帧之间的间隔

public:
	SystemTimeData()
    {
        m_preTime = 0;
        m_curTime = 0;
        m_deltaSec = 0.0f; 
    }

	float getDeltaSec()
    {
        return m_deltaSec;
    }

	void setDeltaSec(float value)
    {
        m_deltaSec = value;
    }

	long getCurTime()
    {
        return m_curTime;
    }
	void setCurTime(long value)
    {
        m_curTime = value;
    }

    void nextFrame()
    {
        m_curTime = DateTime.Now.Ticks;
        if (m_preTime != 0f)     // 第一帧跳过，因为这一帧不好计算间隔
        {
            TimeSpan ts = new TimeSpan(m_curTime - m_preTime);
            m_deltaSec = (float)(ts.TotalSeconds);
        }
        else
        {
            m_deltaSec = 1 / 24;        // 每秒 24 帧
        }
        m_preTime = m_curTime;
    }
};

#endif