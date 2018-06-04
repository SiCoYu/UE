#ifndef __EventDispatchGroup_H
#define __EventDispatchGroup_H

#include "MDictionary.h"
#include "EventDispatchDelegate.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class EventDispatch;

class EventDispatchGroup : public GObject
{
	M_DECLARE_CLASS(EventDispatchGroup, GObject)

protected:
	MDictionary<int, EventDispatch*> mGroupId2DispatchDic;
    bool mIsInLoop;       // 是否是在循环遍历中

public:
	EventDispatchGroup();
    // 添加分发器
	void addEventDispatch(int groupId, EventDispatch* disp);
	void addEventHandle(int groupId, EventDispatchDelegate handle);
	void removeEventHandle(int groupId, EventDispatchDelegate handle);
	void dispatchEvent(int groupId, IDispatchObject* dispatchObject);
	void clearAllEventHandle();
	void clearGroupEventHandle(int groupId);
	bool hasEventHandle(int groupId);
};

MY_END_NAMESPACE

#endif