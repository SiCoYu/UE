#ifndef __TimerItemBase_H
#define __TimerItemBase_H

#include "IDelayHandleItem.h"

/**
    * @brief 定时器，这个是不断增长的
    */
public class TimerItemBase : IDelayHandleItem
{
    public float m_internal;        // 定时器间隔
    public float m_totalTime;      // 总共定时器时间
    public float m_curTime;        // 当前已经调用的定时器的时间
    public bool m_bInfineLoop;  // 是否是无限循环
    public float m_curLeftTimer;    // 当前定时器剩余的次数
    public Action<TimerItemBase> m_timerDisp;       // 定时器分发
    public bool m_disposed;             // 是否已经被释放

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