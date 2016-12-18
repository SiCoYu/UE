#include "MyProject.h"
#include "TickMgr.h"
#include "ITickedObject.h"
#include "TickProcessObject.h"
#include "IDelayHandleItem.h"

TickMgr::TickMgr()
{

}

void TickMgr::addTick(ITickedObject* tickObj, float priority)
{
	addObject((IDelayHandleItem*)tickObj, priority);
}

void TickMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (bInDepth())
	{
		DelayHandleMgrBase::addObject(delayObject, priority);
	}
	else
	{
		int position = -1;
		for (int i = 0; i < mTickList.Count(); i++)
		{
			if (mTickList[i] == nullptr)
				continue;

			if (mTickList[i]->mTickObject == (ITickedObject*)delayObject)
			{
				return;
			}

			if (mTickList[i]->mPriority < priority)
			{
				position = i;
				break;
			}
		}

		TickProcessObject* processObject = new TickProcessObject();
		processObject->mTickObject = (ITickedObject*)delayObject;
		processObject->mPriority = priority;

		if (position < 0 || position >= mTickList.Count())
		{
			mTickList.Add(processObject);
		}
		else
		{
			mTickList.Insert(position, processObject);
		}
	}
}

void TickMgr::delObject(IDelayHandleItem* delayObject)
{
	if (bInDepth())
	{
		DelayHandleMgrBase::delObject(delayObject);
	}
	else
	{
		for(TickProcessObject* item : mTickList.getList())
		{
			if (item->mTickObject == (ITickedObject*)delayObject)
			{
				mTickList.Remove(item);
				break;
			}
		}
	}
}

void TickMgr::Advance(float delta)
{
	incDepth();

	for(TickProcessObject* tk : mTickList.getList())
	{
		if (!((IDelayHandleItem*)(tk->mTickObject))->isClientDispose())
		{
			((ITickedObject*)(tk->mTickObject))->onTick(delta);
		}
	}

	decDepth();
}