#pragma once

#include "DelayNoOrPriorityHandleMgrBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
 */
class DelayPriorityHandleMgrBase : DelayNoOrPriorityHandleMgrBase
{
public:
	DelayPriorityHandleMgrBase()
	{
		this.mDeferredAddQueue = new PriorityList();
		this.mDeferredAddQueue.setIsSpeedUpFind(true);
		this.mDeferredDelQueue = new PriorityList();
		this.mDeferredDelQueue.setIsSpeedUpFind(true);
	}

	virtual void init() override
	{
		Super::init();
	}

	virtual void dispose() override
	{
		if(null != this.mDeferredAddQueue)
		{
			this.mDeferredAddQueue.dispose();
			this.mDeferredAddQueue = null;
		}
		if (null != this.mDeferredDelQueue)
		{
			this.mDeferredDelQueue.dispose();
			this.mDeferredDelQueue = null;
		}

		Super::dispose();
	}
}

MY_END_NAMESPACE