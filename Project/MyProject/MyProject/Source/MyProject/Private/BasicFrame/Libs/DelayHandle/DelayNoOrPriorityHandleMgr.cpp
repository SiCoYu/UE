#include "MyProject.h"
#include "DelayNoOrPriorityHandleMgr.h"
#include "INoOrPriorityObject.h"
#include "ITickedObject.h"
#include "IDelayHandleItem.h"
#include "MClassFactory.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(DelayNoOrPriorityHandleMgr, DelayNoOrPriorityHandleMgrBase)

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
			GLogSys->log("DelayPriorityHandleMgr::_addObject, failed", LogTypeId::eLogCommon);
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
			GLogSys->log("DelayPriorityHandleMgr::_removeObject, failed", LogTypeId::eLogCommon);
		}
	}
}

MY_END_NAMESPACE