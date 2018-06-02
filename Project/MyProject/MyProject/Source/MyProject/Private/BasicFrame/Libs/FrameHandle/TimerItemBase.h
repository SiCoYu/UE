﻿#ifndef __TimerItemBase_H
#define __TimerItemBase_H

#include "PlatformDefine.h"
#include "IDelayHandleItem.h"
#include "IDispatchObject.h"
#include "EventDispatchDelegate.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;

/**
 * @brief 定时器，这个是不断增长的
 */
class TimerItemBase : public IDelayHandleItem, public IDispatchObject
{
public:
    float mInternal;        // 定时器间隔
    float mTotalTime;      // 总共定时器时间
    float mCurTime;        // 当前已经调用的定时器的时间
    bool mIsInfineLoop;  // 是否是无限循环
    float mCurLeftTimer;    // 当前定时器剩余的次数
	AddOnceEventDispatch* mTimerDispatch;       // 定时器分发
    bool mIsDisposed;             // 是否已经被释放

public:
	TimerItemBase();
	virtual ~TimerItemBase();

	void init();
	void dispose();

	void addTimerEventHandle(EventDispatchDelegate handle);
	void removeTimerEventHandle(EventDispatchDelegate handle);

	virtual void OnTimer(float delta);
	virtual void disposeAndDisp();
	virtual void checkAndDisp();
	virtual void reset();
	void setClientDispose();
	bool isClientDispose();
};

MY_END_NAMESPACE

#endif