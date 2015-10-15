#ifndef __EventDispatchGroup_H
#define __EventDispatchGroup_H

#include <map>
#include "EventDispatchDelegate.h"

class EventDispatch;

class EventDispatchGroup
{
protected:
	std::map<int, EventDispatch*> m_groupID2DispatchDic;
    bool m_bInLoop;       // 是否是在循环遍历中

public:
	EventDispatchGroup();
    // 添加分发器
	void addEventDispatch(int groupID, EventDispatch* disp);
	void addEventHandle(int groupID, EventDispatchDelegate handle);
	void removeEventHandle(int groupID, EventDispatchDelegate handle);
	void dispatchEvent(int groupID, IDispatchObject* dispatchObject);
	void clearAllEventHandle();
	void clearGroupEventHandle(int groupID);
};

#endif