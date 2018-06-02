#include "MyProject.h"
#include "DelayHandleMgrBase.h"
#include "DelayHandleObject.h"
#include "DelayAddParam.h"
#include "DelayDelParam.h"
#include "IDelayHandleItem.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayHandleMgrBase::DelayHandleMgrBase()
{
	mLoopDepth = 0;
}

DelayHandleMgrBase::~DelayHandleMgrBase()
{
	
}

void DelayHandleMgrBase::init()
{

}

void DelayHandleMgrBase::dispose()
{

}

// 只有没有添加到列表中的才能添加
bool DelayHandleMgrBase::existAddList(IDelayHandleItem* delayObject)
{
	for(auto item : mDeferredAddQueue.getList())
	{
		if (item->mDelayObject == delayObject)
		{
			return true;
		}
	}

	return false;
}

// 只有没有添加到列表中的才能添加
bool DelayHandleMgrBase::existDelList(IDelayHandleItem* delayObject)
{
	for(auto item : mDeferredDelQueue.getList())
	{
		if (item->mDelayObject == delayObject)
		{
			return true;
		}
	}

	return false;
}

// 从延迟添加列表删除一个 Item
void DelayHandleMgrBase::delFromDelayAddList(IDelayHandleItem* delayObject)
{
	for(auto item : mDeferredAddQueue.getList())
	{
		if (item->mDelayObject == delayObject)
		{
			UtilVector::Remove(mDeferredAddQueue.getList(), item);
		}
	}
}

// 从延迟删除列表删除一个 Item
void DelayHandleMgrBase::delFromDelayDelList(IDelayHandleItem* delayObject)
{
	for(auto item : mDeferredDelQueue.getList())
	{
		if (item->mDelayObject == delayObject)
		{
			UtilVector::Remove(mDeferredDelQueue.getList(), item);
		}
	}
}

void DelayHandleMgrBase::processDelayObjects()
{
	if (0 == mLoopDepth)       // 只有全部退出循环后，才能处理添加删除
	{
		if (mDeferredAddQueue.count() > 0)
		{
			for (int idx = 0; idx < mDeferredAddQueue.count(); idx++)
			{
				addObject(mDeferredAddQueue[idx]->mDelayObject, ((DelayAddParam*)(mDeferredAddQueue[idx]->mDelayParam))->mPriority);
			}

			mDeferredAddQueue.clear();
		}

		if (mDeferredDelQueue.count() > 0)
		{
			for (int idx = 0; idx < mDeferredDelQueue.count(); idx++)
			{
				delObject(mDeferredDelQueue[idx]->mDelayObject);
			}

			mDeferredDelQueue.clear();
		}
	}
}

void DelayHandleMgrBase::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (mLoopDepth > 0)
	{
		if (!existAddList(delayObject))        // 如果添加列表中没有
		{
			if (existDelList(delayObject))    // 如果已经添加到删除列表中
			{
				delFromDelayDelList(delayObject);
			}

			DelayHandleObject* delayHandleObject = new DelayHandleObject();
			delayHandleObject->mDelayParam = new DelayAddParam();
			mDeferredAddQueue.add(delayHandleObject);

			delayHandleObject->mDelayObject = delayObject;
			((DelayAddParam*)(delayHandleObject->mDelayParam))->mPriority = priority;
		}
	}
}

void DelayHandleMgrBase::delObject(IDelayHandleItem* delayObject)
{
	if (mLoopDepth > 0)
	{
		if (!existDelList(delayObject))
		{
			if (existAddList(delayObject))    // 如果已经添加到删除列表中
			{
				delFromDelayAddList(delayObject);
			}

			delayObject->setClientDispose();

			DelayHandleObject* delayHandleObject = new DelayHandleObject();
			delayHandleObject->mDelayParam = new DelayDelParam();
			mDeferredDelQueue.add(delayHandleObject);
			delayHandleObject->mDelayObject = delayObject;
		}
	}
}

void DelayHandleMgrBase::incDepth()
{
	++mLoopDepth;
}

void DelayHandleMgrBase::decDepth()
{
	--mLoopDepth;
	processDelayObjects();
}

bool DelayHandleMgrBase::isInDepth()
{
	return mLoopDepth > 0;
}

MY_END_NAMESPACE