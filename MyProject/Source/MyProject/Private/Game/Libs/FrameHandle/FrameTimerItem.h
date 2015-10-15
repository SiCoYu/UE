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

public:
	FrameTimerItem();
	virtual void OnFrameTimer();
	virtual void reset();
	void setClientDispose();
	bool getClientDispose();
};

#endif