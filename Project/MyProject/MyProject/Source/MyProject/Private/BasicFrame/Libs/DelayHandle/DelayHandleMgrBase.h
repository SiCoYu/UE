#ifndef __DelayHandleMgrBase_H
#define __DelayHandleMgrBase_H

#include "MList.h"

class DelayHandleObject;
class IDelayHandleItem;

/**
    * @brief 当需要管理的对象可能在遍历中间添加的时候，需要这个管理器
    */
class DelayHandleMgrBase
{
protected:
	MList<DelayHandleObject*> mDeferredAddQueue;
    MList<DelayHandleObject*> mDeferredDelQueue;

    int mLoopDepth;           // 是否在循环中，支持多层嵌套，就是循环中再次调用循环

protected:
	// 只有没有添加到列表中的才能添加
	bool existAddList(IDelayHandleItem* delayObject);
	// 只有没有添加到列表中的才能添加
	bool existDelList(IDelayHandleItem* delayObject);
	// 从延迟添加列表删除一个 Item
	void delFromDelayAddList(IDelayHandleItem* delayObject);
	// 从延迟删除列表删除一个 Item
	void delFromDelayDelList(IDelayHandleItem* delayObject);
	void processDelayObjects();

public:
	DelayHandleMgrBase();
	virtual ~DelayHandleMgrBase();

	virtual void init();
	virtual void dispose();

	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f);
	virtual void delObject(IDelayHandleItem* delayObject);
	void incDepth();
	void decDepth();
	bool isInDepth();
};

#endif