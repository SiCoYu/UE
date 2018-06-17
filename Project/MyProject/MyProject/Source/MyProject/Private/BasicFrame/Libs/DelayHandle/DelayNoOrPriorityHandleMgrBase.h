#pragma once

#include "GObject.h"
#include "TypeDef.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityList;
class LoopDepth;
class IDispatchObject;
class IDelayHandleItem;

/**
 * @brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
 */
class DelayNoOrPriorityHandleMgrBase : public GObject
{
	M_DECLARE_CLASS(DelayNoOrPriorityHandleMgrBase, GObject)

protected:
	INoOrPriorityList* mDeferredAddQueue;
	INoOrPriorityList* mDeferredRemoveQueue;

	LoopDepth* mLoopDepth;         // 是否在循环中，支持多层嵌套，就是循环中再次调用循环
	int mDebugUniqueId;           // 唯一 Id ，调试使用
	bool mIsDispose;              // 是否被释放

public:
	DelayNoOrPriorityHandleMgrBase();

	virtual void init();
	virtual void dispose();
	int getDebugUniqueId();

protected:
	virtual void _addObject(
		IDelayHandleItem* delayObject, 
		float priority = 0.0f
	);

	virtual void _removeObject(IDelayHandleItem* delayObject);

	// 只要调用会添加或者删除列表元素，就需要调用这个接口
	void _incDepth();
	void _decDepth();
	bool _isInDepth();

private:
	void _processDelayObjects(
		IDispatchObject* dispObj, 
		uint eventId = 0
	);
};

MY_END_NAMESPACE