#include "MyProject.h"
#include "DelayNoOrPriorityHandleMgr.h"
#include "INoOrPriorityObject.h"
#include "ITickedObject.h"
#include "IDelayHandleItem.h"

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
	bool ret = (this->mNoOrPriorityList.count() == 0);
	return ret;
}

void DelayNoOrPriorityHandleMgr::addNoOrPriorityObject(INoOrPriorityObject* priorityObject, float priority)
{
	this->_addObject((IDelayHandleItem*)priorityObject, priority);
}

void DelayNoOrPriorityHandleMgr::removeNoOrPriorityObject(ITickedObject* tickObj)
{
	this->_removeObject((IDelayHandleItem*)tickObj);
}

void DelayNoOrPriorityHandleMgr::_addObject(IDelayHandleItem* delayObject, float priority)
{
	if (nullptr != delayObject)
	{
		if (this->_isInDepth())
		{
			Super::_addObject(delayObject, priority);
		}
		else
		{
			if (!this->mNoOrPriorityList.contains((INoOrPriorityObject*)delayObject))
			{
				this->mNoOrPriorityList.addNoOrPriorityObject((INoOrPriorityObject*)delayObject, priority);
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

void DelayNoOrPriorityHandleMgr::_removeObject(IDelayHandleItem* delayObject)
{
	if (nullptr != delayObject)
	{
		if (this->_isInDepth())
		{
			Super::_removeObject(delayObject);
		}
		else
		{
			if(this->mNoOrPriorityList.contains((INoOrPriorityObject*)delayObject))
			{
				this->mNoOrPriorityList.removeNoOrPriorityObject((INoOrPriorityObject*)delayObject);
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