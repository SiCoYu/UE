#ifndef __EventDispatchFunctionObject_H
#define __EventDispatchFunctionObject_H

#include "IDelayHandleItem.h"
#include "EventDispatchDelegate.h"

class EventDispatchFunctionObject : public IDelayHandleItem
{
public:
	bool m_bClientDispose;       // 是否释放了资源
	EventDispatchDelegate m_handle;

public:
	EventDispatchFunctionObject();
	void setClientDispose();
	bool getClientDispose();
};

#endif