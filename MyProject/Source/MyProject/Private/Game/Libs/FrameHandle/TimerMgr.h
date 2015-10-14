#ifndef __TimerMgr_H
#define __TimerMgr_H

#include "MList.h"

class TimerItemBase;
class IDelayHandleItem;

/**
* @brief 定时器管理器
*/
public class TimerMgr : DelayHandleMgrBase
{
protected:
	MList<TimerItemBase*> m_timerLists;     // 当前所有的定时器列表

public:
	TimerMgr();
	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void delObject(IDelayHandleItem* delayObject) override;
	void Advance(float delta);
};

#endif