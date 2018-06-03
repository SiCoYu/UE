#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 时间间隔
 */
class TimeInterval
{
protected:
	float mInterval;
    float mTotalTime;
    float mCurTime;

    int mTotalExecNum;    // 总共执行次数
    int mCurExecNum;      // 执行的次数

public:
	TimeInterval()

    void setInterval(float value)
    void setTotalTime(float value)
    void setCurTime(float value)
    void setTotalExecNum(int value)
    void setCurExecNum(int value)
    // 当前是否满足间隔条件
    bool canExec(float delta)
    // 是否执行结束
    bool isExecEnd()
};

MY_END_NAMESPACE