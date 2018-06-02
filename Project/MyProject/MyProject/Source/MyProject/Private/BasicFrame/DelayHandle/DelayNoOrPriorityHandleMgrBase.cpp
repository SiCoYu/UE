#include "MyProject.h"
#include "DelayNoOrPriorityHandleMgrBase.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoOrPriorityHandleMgrBase::DelayNoOrPriorityHandleMgrBase()
{
	this.mIsDispose = false;
	this.mLoopDepth = new LoopDepth();
	this.mLoopDepth.setZeroHandle(null, this._processDelayObjects, 0);

	if(MacroDef.DEBUG_SYS)
	{
		this.mDebugUniqueId = (int)Ctx.msInstance.mDebugSys.mDebugPriorityHandleUniqueId.genNewId();
	}
}

virtual void DelayNoOrPriorityHandleMgrBase::init()
{

}

virtual void DelayNoOrPriorityHandleMgrBase::dispose()
{
	this.mIsDispose = true;

	if (null != this.mDeferredAddQueue)
	{
		this.mDeferredAddQueue.dispose();
		this.mDeferredAddQueue = null;
	}
	if (null != this.mDeferredDelQueue)
	{
		this.mDeferredDelQueue.dispose();
		this.mDeferredDelQueue = null;
	}
	if (null != this.mLoopDepth)
	{
		this.mLoopDepth.dispose();
		this.mLoopDepth = null;
	}
}

int DelayNoOrPriorityHandleMgrBase::getDebugUniqueId()
{
	return this.mDebugUniqueId;
}

void DelayNoOrPriorityHandleMgrBase::_addObject(IDelayHandleItem delayObject, float priority)
{
	if(this.mLoopDepth._isInDepth())
	{
		// 如果添加列表中没有
		if (!this.mDeferredAddQueue.contains(delayObject as INoOrPriorityObject))
		{
			// 如果已经添加到删除列表中
			if (this.mDeferredDelQueue.contains(delayObject as INoOrPriorityObject))
			{
				this.mDeferredDelQueue.removeNoOrPriorityObject(delayObject as INoOrPriorityObject);
			}
			
			this.mDeferredAddQueue.addNoOrPriorityObject(delayObject as INoOrPriorityObject, priority);
		}
	}
}

void DelayNoOrPriorityHandleMgrBase::_removeObject(IDelayHandleItem delayObject)
{
	if (delayObject is INoOrPriorityObject)
	{
		if (this.mLoopDepth._isInDepth())
		{
			if (!this.mDeferredDelQueue.contains(delayObject as INoOrPriorityObject))
			{
				if (this.mDeferredAddQueue.contains(delayObject as INoOrPriorityObject))    // 如果已经添加到删除列表中
				{
					this.mDeferredAddQueue.removeNoOrPriorityObject(delayObject as INoOrPriorityObject);
				}

				delayObject.setClientDispose(true);

				this.mDeferredDelQueue.addNoOrPriorityObject(delayObject as INoOrPriorityObject);
			}
		}
	}
	else
	{
		Ctx.msInstance.mLogSys.log("delayObject is not INoOrPriorityObject", LogTypeId.eLogDataStruct);
	}
}

// 只要调用会添加或者删除列表元素，就需要调用这个接口
void DelayNoOrPriorityHandleMgrBase::_incDepth()
{
	this.mLoopDepth._incDepth();
}

// 只要调用会添加或者删除列表元素，就需要调用这个接口
void DelayNoOrPriorityHandleMgrBase::_decDepth()
{
	if (null != this.mLoopDepth)
	{
		this.mLoopDepth._decDepth();
	}
	else
	{
		// 已经释放了资源，不用再处理了
	}
}

bool DelayNoOrPriorityHandleMgrBase::_isInDepth()
{
	bool ret = false;

	if (null != this.mLoopDepth)
	{
		ret = this.mLoopDepth._isInDepth();
	}
	else
	{
		// 资源已经释放
	}

	return ret;
}

void DelayNoOrPriorityHandleMgrBase::_processDelayObjects(IDispatchObject dispObj, uint eventId)
{
	int idx = 0;
	// len 是 Python 的关键字
	int elemLen = 0;

	if (!this.mLoopDepth._isInDepth())       // 只有全部退出循环后，才能处理添加删除
	{
		if (this.mDeferredAddQueue.count() > 0)
		{
			idx = 0;
			elemLen = this.mDeferredAddQueue.count();

			while(idx < elemLen)
			{
				this._addObject(this.mDeferredAddQueue.get(idx) as IDelayHandleItem);

				idx += 1;
			}

			this.mDeferredAddQueue.clear();
		}

		if (this.mDeferredDelQueue.count() > 0)
		{
			idx = 0;
			elemLen = this.mDeferredDelQueue.count();

			while(idx < elemLen)
			{
				this._removeObject(this.mDeferredDelQueue.get(idx) as IDelayHandleItem);

				idx += 1;
			}

			this.mDeferredDelQueue.clear();
		}
	}
}

MY_END_NAMESPACE