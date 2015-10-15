#ifndef __FrameTimerMgr_H
#define __FrameTimerMgr_H

#include "DelayHandleMgrBase.h"
#include <vector>

class FrameTimerItem;

/**
* @brief 定时器管理器
*/
class FrameTimerMgr : public DelayHandleMgrBase
{
protected:
	std::vector<FrameTimerItem*> m_timerLists;     // 当前所有的定时器列表
	std::vector<FrameTimerItem*> m_delLists;       // 当前需要删除的定时器

public:
	FrameTimerMgr();
	virtual void addObject(IDelayHandleItem delayObject, float priority = 0.0f) override;
	virtual void delObject(IDelayHandleItem delayObject) override;
	void Advance(float delta);
};

#endif