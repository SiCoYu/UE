#ifndef __FrameTimerMgr_H
#define __FrameTimerMgr_H

#include "DelayHandleMgrBase.h"
#include <vector>
#include "BaseClassDef.h"

class FrameTimerItem;

/**
* @brief 定时器管理器
*/
class FrameTimerMgr : public DelayHandleMgrBase
{
	M_DECLARE_SUPER_KW(DelayHandleMgrBase)

protected:
	std::vector<FrameTimerItem*> mTimerList;     // 当前所有的定时器列表
	std::vector<FrameTimerItem*> mDelList;       // 当前需要删除的定时器

public:
	FrameTimerMgr();
	virtual ~FrameTimerMgr();

public:
	virtual void init();
	virtual void dispose();

	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void delObject(IDelayHandleItem* delayObject) override;
	void Advance(float delta);
};

#endif