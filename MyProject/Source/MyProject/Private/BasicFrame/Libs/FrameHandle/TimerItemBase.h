#ifndef __TimerItemBase_H
#define __TimerItemBase_H

#include "IDelayHandleItem.h"
#include "TimerDelegate.h"

/**
 * @brief 定时器，这个是不断增长的
 */
class TimerItemBase : public IDelayHandleItem
{
public:
    float m_internal;        // 定时器间隔
    float m_totalTime;      // 总共定时器时间
    float m_curTime;        // 当前已经调用的定时器的时间
    bool m_bInfineLoop;  // 是否是无限循环
    float m_curLeftTimer;    // 当前定时器剩余的次数
	TimerDelegate m_timerDisp;       // 定时器分发
    bool m_disposed;             // 是否已经被释放

public:
	TimerItemBase();
	virtual void OnTimer(float delta);
	virtual void disposeAndDisp();
	virtual void checkAndDisp();
	virtual void reset();
	void setClientDispose();
	bool getClientDispose();
};

#endif