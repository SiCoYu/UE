#ifndef __FrameTimerItem_H
#define __FrameTimerItem_H

#include "IDelayHandleItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 定时器，这个是不断增长的
 */
class FrameTimerItem : public IDelayHandleItem
{
public:
	int mInternal;              // 帧数间隔
    int mTotalFrameCount;       // 总共次数
    int mCurFrame;              // 当前已经调用的定时器的时间
    int mCurLeftFrame;          // 剩余帧数
    bool mIsInfineLoop;      // 是否是无限循环
	FrameTimerDelegate mTimerDispatch;       // 定时器分发
    bool mIsDisposed;             // 是否已经被释放

    //int m_preFrame = 0;

public:
	FrameTimerItem();
	virtual void OnFrameTimer();
	virtual void reset();
	void setClientDispose();
	bool isClientDispose();
};

MY_END_NAMESPACE

#endif