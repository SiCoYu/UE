#ifndef __TimerMgr_H
#define __TimerMgr_H

#include "DelayPriorityHandleMgrBase.h"
#include "MList.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TimerItemBase;
class IDelayHandleItem;

/**
* @brief 定时器管理器
*/
class TimerMgr : public DelayPriorityHandleMgrBase
{
	M_DECLARE_CLASS(TimerMgr, DelayPriorityHandleMgrBase)

protected:
	MList<TimerItemBase*> mTimerList;     // 当前所有的定时器列表

public:
	TimerMgr();
	virtual ~TimerMgr();

public:
	virtual void init();
	virtual void dispose();
	void addTimer(TimerItemBase* delayObject, float priority = 0.0f);
	void removeTimer(TimerItemBase* timer);
	void advance(float delta);

protected:
	virtual void _addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void _removeObject(IDelayHandleItem* delayObject) override;
};

MY_END_NAMESPACE

#endif