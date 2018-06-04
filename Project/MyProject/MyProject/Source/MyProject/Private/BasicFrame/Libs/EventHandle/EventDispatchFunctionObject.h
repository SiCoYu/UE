#ifndef __EventDispatchFunctionObject_H
#define __EventDispatchFunctionObject_H

#include "GObject.h"
#include "IDelayHandleItem.h"
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class EventDispatchFunctionObject : public GObject, public IDelayHandleItem
{
public:
	bool mIsClientDispose;       // 是否释放了资源
	EventDispatchDelegate mHandle;

public:
	EventDispatchFunctionObject();
	void setClientDispose(bool isDispose);
	bool isClientDispose();
};

MY_END_NAMESPACE

#endif