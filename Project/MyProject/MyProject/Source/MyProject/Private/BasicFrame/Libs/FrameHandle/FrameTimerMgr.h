#ifndef __FrameTimerMgr_H
#define __FrameTimerMgr_H

#include "DelayPriorityHandleMgrBase.h"
#include "MList.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class FrameTimerItem;

/**
* @brief 定时器管理器
*/
class FrameTimerMgr : public DelayPriorityHandleMgrBase
{
	M_DECLARE_CLASS(FrameTimerMgr, DelayPriorityHandleMgrBase)

protected:
	MList<FrameTimerItem*> mTimerList;     // 当前所有的定时器列表

public:
	FrameTimerMgr();
	virtual ~FrameTimerMgr();

public:
	virtual void init();
	virtual void dispose();

	void addFrameTimer(FrameTimerItem* timer, float priority = 0.0f);
	void removeFrameTimer(FrameTimerItem* timer);
	void advance(float delta);

protected:
	virtual void _addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void _removeObject(IDelayHandleItem* delayObject) override;
};

MY_END_NAMESPACE

#endif