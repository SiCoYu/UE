#pragma once

#include "DelayNoOrPriorityHandleMgr.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 延迟优先级处理管理器
 */
class DelayNoPriorityHandleMgr : public DelayNoOrPriorityHandleMgr
{
public:
	DelayNoPriorityHandleMgr();
	virtual void init() override;
	virtual void dispose() override;
	void addNoPriorityObject(INoOrPriorityObject* priorityObject);
	void removeNoPriorityObject(ITickedObject* tickObj);
};

MY_END_NAMESPACE