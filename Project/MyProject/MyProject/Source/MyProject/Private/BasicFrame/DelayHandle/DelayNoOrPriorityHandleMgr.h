#pragma once

#include "DelayNoOrPriorityHandleMgrBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 延迟优先级处理管理器
 */
class DelayNoOrPriorityHandleMgr : public DelayNoOrPriorityHandleMgrBase
{
protected:
	INoOrPriorityList mNoOrPriorityList;

public:
	DelayNoOrPriorityHandleMgr()
	{

	}

	virtual void init() override
	{
		Super::init();
	}

	virtual void dispose() override
	{
		Super::dispose();
	}

	bool isEmpty()
	{
		bool ret = (this.mNoOrPriorityList.count() == 0);
		return ret;
	}

protected:
	virtual void _addObject(IDelayHandleItem delayObject, float priority = 0.0f) override
	{
		if (null != delayObject)
		{
			if (this._isInDepth())
			{
				base._addObject(delayObject, priority);
			}
			else
			{
				if (!this.mNoOrPriorityList.contains(delayObject as INoOrPriorityObject))
				{
					this.mNoOrPriorityList.addNoOrPriorityObject(delayObject as INoOrPriorityObject, priority);
				}
			}
		}
		else
		{
			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log("DelayPriorityHandleMgr::_addObject, failed", LogTypeId.eLogCommon);
			}
		}
	}

	virtual void _removeObject(IDelayHandleItem delayObject) override
	{
		if (null != delayObject)
		{
			if (this._isInDepth())
			{
				base._removeObject(delayObject);
			}
			else
			{
				if(this.mNoOrPriorityList.contains(delayObject as INoOrPriorityObject))
				{
					this.mNoOrPriorityList.removeNoOrPriorityObject(delayObject as INoOrPriorityObject);
				}
			}
		}
		else
		{
			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log("DelayPriorityHandleMgr::_removeObject, failed", LogTypeId.eLogCommon);
			}
		}
	}

public:
	void addNoOrPriorityObject(INoOrPriorityObject priorityObject, float priority = 0.0f)
	{
		this._addObject(priorityObject as IDelayHandleItem, priority);
	}

	void removeNoOrPriorityObject(ITickedObject tickObj)
	{
		this._removeObject(tickObj as IDelayHandleItem);
	}
}

MY_END_NAMESPACE