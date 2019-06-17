#ifndef __SystemTimeData_H
#define __SystemTimeData_H

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SystemTimeData : public GObject
{
protected:
	long mPreTime;           // 上一次更新时的秒数
    long mCurTime;           // 正在获取的时间
    float mDeltaSec;         // 两帧之间的间隔
	bool mIsFixFrameRate;     // 固定帧率
	float mFixFrameRate;      // 固定帧率
	float mScale;             // delta 缩放

	float mFixedTimestep;

public:
	SystemTimeData();

public:
	void init();
	void dispose();

	float getDeltaSec();
	void setDeltaSec(float value);
	long getCurTime();
	void setCurTime(long value);
	float getFixedTimestep();
	// 获取固定帧率时间间隔
	float getFixFrameRateInterval();
	void nextFrame();
};

MY_END_NAMESPACE

#endif