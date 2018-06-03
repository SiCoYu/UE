#pragma once

#include "DelayNoOrPriorityHandleMgrBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityObject;
class ITickedObject;
class IDelayHandleItem;

/**
 * @brief 延迟优先级处理管理器
 */
class DelayNoOrPriorityHandleMgr : public DelayNoOrPriorityHandleMgrBase
{
protected:
	INoOrPriorityList mNoOrPriorityList;

public:
	DelayNoOrPriorityHandleMgr();

	virtual void init() override;
	virtual void dispose() override;
	bool isEmpty();
	void addNoOrPriorityObject(INoOrPriorityObject* priorityObject, float priority = 0.0f);
	void removeNoOrPriorityObject(ITickedObject* tickObj);

protected:
	virtual void _addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void _removeObject(IDelayHandleItem* delayObject) override;
};

MY_END_NAMESPACE