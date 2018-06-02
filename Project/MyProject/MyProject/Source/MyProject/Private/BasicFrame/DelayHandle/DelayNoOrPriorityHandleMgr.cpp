#include "MyProject.h"
#include "DelayNoOrPriorityHandleMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoOrPriorityHandleMgr::DelayNoOrPriorityHandleMgr()
{

}

void DelayNoOrPriorityHandleMgr::init() 
{
	Super::init();
}

void DelayNoOrPriorityHandleMgr::dispose()
{
	Super::dispose();
}

bool DelayNoOrPriorityHandleMgr::isEmpty()
{
	bool ret = (this.mNoOrPriorityList.count() == 0);
	return ret;
}

void DelayNoOrPriorityHandleMgr::addNoOrPriorityObject(INoOrPriorityObject priorityObject, float priority)
{
	this._addObject(priorityObject as IDelayHandleItem, priority);
}

void DelayNoOrPriorityHandleMgr::removeNoOrPriorityObject(ITickedObject tickObj)
{
	this._removeObject(tickObj as IDelayHandleItem);
}

void DelayNoOrPriorityHandleMgr::_addObject(IDelayHandleItem delayObject, float priority)
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

void DelayNoOrPriorityHandleMgr::_removeObject(IDelayHandleItem delayObject)
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

MY_END_NAMESPACE