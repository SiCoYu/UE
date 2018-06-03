#pragma once

#include "DelayNoOrPriorityHandleMgrBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
 */
class DelayNoPriorityHandleMgrBase : public DelayNoOrPriorityHandleMgrBase
{
public:
	DelayNoPriorityHandleMgrBase();

	virtual void init() override;
	virtual void dispose() override;
};

MY_END_NAMESPACE