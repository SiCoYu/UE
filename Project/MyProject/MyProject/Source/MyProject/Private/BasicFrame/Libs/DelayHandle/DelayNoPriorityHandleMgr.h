#pragma once

#include "DelayNoOrPriorityHandleMgr.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityObject;
class ITickedObject;

/**
 * @brief 延迟优先级处理管理器
 */
class DelayNoPriorityHandleMgr : public DelayNoOrPriorityHandleMgr
{
	M_DECLARE_CLASS(DelayNoPriorityHandleMgr, DelayNoOrPriorityHandleMgr)

public:
	DelayNoPriorityHandleMgr();
	virtual void init() override;
	virtual void dispose() override;
	void addNoPriorityObject(INoOrPriorityObject* priorityObject);
	void removeNoPriorityObject(ITickedObject* tickObj);
};

MY_END_NAMESPACE