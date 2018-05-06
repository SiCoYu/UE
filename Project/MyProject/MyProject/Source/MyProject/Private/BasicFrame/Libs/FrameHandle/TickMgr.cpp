#include "MyProject.h"
#include "TickMgr.h"
#include "ITickedObject.h"
#include "TickProcessObject.h"
#include "IDelayHandleItem.h"

TickMgr::TickMgr()
{

}

TickMgr::~TickMgr()
{

}

void TickMgr::init()
{
	Super::init();
}

void TickMgr::dispose()
{
	Super::dispose();
}

void TickMgr::addTick(ITickedObject* tickObj, float priority)
{
	this->addObject((IDelayHandleItem*)tickObj, priority);
}

void TickMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (this->isInDepth())
	{
		DelayHandleMgrBase::addObject(delayObject, priority);
	}
	else
	{
		int position = -1;

		for (int i = 0; i < mTickList.Count(); i++)
		{
			if (this->mTickList[i] == nullptr)
				continue;

			if (this->mTickList[i]->mTickObject == (ITickedObject*)delayObject)
			{
				return;
			}

			if (this->mTickList[i]->mPriority < priority)
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
			this->mTickList.Add(processObject);
		}
		else
		{
			this->mTickList.Insert(position, processObject);
		}
	}
}

void TickMgr::delObject(IDelayHandleItem* delayObject)
{
	if (this->isInDepth())
	{
		DelayHandleMgrBase::delObject(delayObject);
	}
	else
	{
		for(TickProcessObject* item : this->mTickList.getList())
		{
			if (item->mTickObject == (ITickedObject*)delayObject)
			{
				this->mTickList.Remove(item);
				break;
			}
		}
	}
}

void TickMgr::Advance(float delta)
{
	this->incDepth();

	for(TickProcessObject* tk : this->mTickList.getList())
	{
		if (!((IDelayHandleItem*)(tk->mTickObject))->isClientDispose())
		{
			((ITickedObject*)(tk->mTickObject))->onTick(delta);
		}
	}

	this->decDepth();
}