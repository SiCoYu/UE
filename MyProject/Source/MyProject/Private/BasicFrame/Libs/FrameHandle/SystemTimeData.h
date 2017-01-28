#ifndef __SystemTimeData_H
#define __SystemTimeData_H

class SystemTimeData
{
protected:
	long mPreTime;           // 上一次更新时的秒数
    long mCurTime;           // 正在获取的时间
    float mDeltaSec;         // 两帧之间的间隔

public:
	SystemTimeData();

public:
	void init();
	void dispose();

	float getDeltaSec();
	void setDeltaSec(float value);
	long getCurTime();
	void setCurTime(long value);
	void nextFrame();
};

#endif