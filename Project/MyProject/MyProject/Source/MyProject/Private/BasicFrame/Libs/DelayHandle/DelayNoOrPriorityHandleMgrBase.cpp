#include "MyProject.h"
#include "DelayNoOrPriorityHandleMgrBase.h"
#include "LoopDepth.h"
#include "IDispatchObject.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "EventDispatchDelegate.h"
#include "MClassFactory.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"
#include "INoOrPriorityList.h"
#include "IDelayHandleItem.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(DelayNoOrPriorityHandleMgrBase, GObject)

DelayNoOrPriorityHandleMgrBase::DelayNoOrPriorityHandleMgrBase()
{
	this->mIsDispose = false;

	// 如果在构造函数中执行，会递归构造 AddOnceEventDispatch ，造成死循环
	this->mLoopDepth = MY_NEW LoopDepth();
	this->mLoopDepth->setZeroHandle(
		MakeEventDispatchDelegate(
			this,
			&DelayNoOrPriorityHandleMgrBase::_processDelayObjects
		)
	);

	if (MacroDef::DEBUG_SYS)
	{
		//this->mDebugUniqueId = (int)Ctx.msInstance.mDebugSys.mDebugPriorityHandleUniqueId.genNewId();
	}
}

void DelayNoOrPriorityHandleMgrBase::init()
{
	
}

void DelayNoOrPriorityHandleMgrBase::dispose()
{
	this->mIsDispose = true;

	if (nullptr != this->mDeferredAddQueue)
	{
		this->mDeferredAddQueue->dispose();
		MY_DELETE this->mDeferredAddQueue;
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredDelQueue)
	{
		this->mDeferredDelQueue->dispose();
		MY_DELETE this->mDeferredDelQueue;
		this->mDeferredDelQueue = nullptr;
	}
	if (nullptr != this->mLoopDepth)
	{
		this->mLoopDepth->dispose();
		MY_DELETE this->mLoopDepth;
		this->mLoopDepth = nullptr;
	}
}

int DelayNoOrPriorityHandleMgrBase::getDebugUniqueId()
{
	return this->mDebugUniqueId;
}

void DelayNoOrPriorityHandleMgrBase::_addObject(IDelayHandleItem* delayObject, float priority)
{
	if(this->mLoopDepth->_isInDepth())
	{
		// 如果添加列表中没有
		if (!this->mDeferredAddQueue->contains((INoOrPriorityObject*)delayObject))
		{
			// 如果已经添加到删除列表中
			if (this->mDeferredDelQueue->contains((INoOrPriorityObject*)delayObject))
			{
				this->mDeferredDelQueue->removeNoOrPriorityObject((INoOrPriorityObject*)delayObject);
			}
			
			this->mDeferredAddQueue->addNoOrPriorityObject((INoOrPriorityObject*)delayObject, priority);
		}
	}
}

void DelayNoOrPriorityHandleMgrBase::_removeObject(IDelayHandleItem* delayObject)
{
	if (delayObject)
	{
		if (this->mLoopDepth->_isInDepth())
		{
			if (!this->mDeferredDelQueue->contains((INoOrPriorityObject*)delayObject))
			{
				if (this->mDeferredAddQueue->contains((INoOrPriorityObject*)delayObject))    // 如果已经添加到删除列表中
				{
					this->mDeferredAddQueue->removeNoOrPriorityObject((INoOrPriorityObject*)delayObject);
				}

				delayObject->setClientDispose(true);

				this->mDeferredDelQueue->addNoOrPriorityObject((INoOrPriorityObject*)delayObject);
			}
		}
	}
	else
	{
		GLogSys->log("delayObject is not INoOrPriorityObject", LogTypeId::eLogDataStruct);
	}
}

// 只要调用会添加或者删除列表元素，就需要调用这个接口
void DelayNoOrPriorityHandleMgrBase::_incDepth()
{
	this->mLoopDepth->_incDepth();
}

// 只要调用会添加或者删除列表元素，就需要调用这个接口
void DelayNoOrPriorityHandleMgrBase::_decDepth()
{
	if (nullptr != this->mLoopDepth)
	{
		this->mLoopDepth->_decDepth();
	}
	else
	{
		// 已经释放了资源，不用再处理了
	}
}

bool DelayNoOrPriorityHandleMgrBase::_isInDepth()
{
	bool ret = false;

	if (nullptr != this->mLoopDepth)
	{
		ret = this->mLoopDepth->_isInDepth();
	}
	else
	{
		// 资源已经释放
	}

	return ret;
}

void DelayNoOrPriorityHandleMgrBase::_processDelayObjects(IDispatchObject* dispObj/*, uint eventId*/)
{
	int idx = 0;
	// len 是 Python 的关键字
	int elemLen = 0;

	if (!this->mLoopDepth->_isInDepth())       // 只有全部退出循环后，才能处理添加删除
	{
		if (this->mDeferredAddQueue->count() > 0)
		{
			idx = 0;
			elemLen = this->mDeferredAddQueue->count();

			while(idx < elemLen)
			{
				this->_addObject((IDelayHandleItem*)this->mDeferredAddQueue->get(idx));

				idx += 1;
			}

			this->mDeferredAddQueue->clear();
		}

		if (this->mDeferredDelQueue->count() > 0)
		{
			idx = 0;
			elemLen = this->mDeferredDelQueue->count();

			while(idx < elemLen)
			{
				this->_removeObject((IDelayHandleItem*)this->mDeferredDelQueue->get(idx));

				idx += 1;
			}

			this->mDeferredDelQueue->clear();
		}
	}
}

MY_END_NAMESPACE