#ifndef __EventDispatch_H
#define __EventDispatch_H

#include "DelayHandleMgrBase.h"
#include "MList.h"
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"

class EventDispatchFunctionObject;

/**
 * @brief 事件分发，之分发一类事件，不同类型的事件使用不同的事件分发
 * @brief 注意，事件分发缺点就是，可能被调用的对象已经释放，但是没有清掉事件处理器，结果造成空指针
 */
class EventDispatch : public DelayHandleMgrBase
{
	M_DECLARE_SUPER_KW(DelayHandleMgrBase)

protected :
	int mEventId;
    MList<EventDispatchFunctionObject*> mHandleList;
    int mUniqueId;       // 唯一 Id ，调试使用
    //LuaCSBridgeDispatch m_luaCSBridgeDispatch;

protected:
	MList<EventDispatchFunctionObject*>& getHandleList();

public:
	EventDispatch(int eventId_ = 0);
	int getUniqueId();
	void setUniqueId(int value);
    //public LuaCSBridgeDispatch luaCSBridgeDispatch;
    // 相同的函数只能增加一次
	virtual void addEventHandle(EventDispatchDelegate handle);
	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	void removeEventHandle(EventDispatchDelegate handle);
	virtual void delObject(IDelayHandleItem* delayObject) override;
	virtual void dispatchEvent(IDispatchObject* dispatchObject);
	void clearEventHandle();
    // 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
	bool isExistEventHandle(EventDispatchDelegate handle);
	void copyFrom(EventDispatch& rhv);
};

#endif