#ifndef __TimerMgr_H
#define __TimerMgr_H

#include "DelayHandleMgrBase.h"
#include "MList.h"
#include "BaseClassDef.h"

class TimerItemBase;
class IDelayHandleItem;

/**
* @brief 定时器管理器
*/
class TimerMgr : public DelayHandleMgrBase
{
	M_DECLARE_SUPER_KW(DelayHandleMgrBase)

protected:
	MList<TimerItemBase*> mTimerList;     // 当前所有的定时器列表

public:
	TimerMgr();
	virtual ~TimerMgr();

public:
	virtual void init();
	virtual void dispose();

	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void delObject(IDelayHandleItem* delayObject) override;
	void Advance(float delta);
};

#endif