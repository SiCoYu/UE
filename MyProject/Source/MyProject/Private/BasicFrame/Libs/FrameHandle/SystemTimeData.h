#ifndef __SystemTimeData_H
#define __SystemTimeData_H

class SystemTimeData
{
protected:
	long m_preTime;           // 上一次更新时的秒数
    long m_curTime;           // 正在获取的时间
    float m_deltaSec;         // 两帧之间的间隔

public:
	SystemTimeData();
	float getDeltaSec();
	void setDeltaSec(float value);
	long getCurTime();
	void setCurTime(long value);
	void nextFrame();
};

#endif