#pragma once

#include "DelayNoOrPriorityHandleMgr.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityObject;
class ITickedObject;

/**
 * @brief 延迟优先级处理管理器
 */
class DelayPriorityHandleMgr : public DelayNoOrPriorityHandleMgr
{
public:
	DelayPriorityHandleMgr();
	
	virtual void init() override;
	virtual void dispose() override;
	void addPriorityObject(INoOrPriorityObject* priorityObject, float priority = 0.0f);
	void removePriorityObject(ITickedObject* tickObj);
};

MY_END_NAMESPACE