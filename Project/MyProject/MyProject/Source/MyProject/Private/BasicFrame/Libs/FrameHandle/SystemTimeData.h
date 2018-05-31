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

MY_END_NAMESPACE

#endif