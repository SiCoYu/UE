#ifndef __EventDispatchFunctionObject_H
#define __EventDispatchFunctionObject_H

#include "IDelayHandleItem.h"
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class EventDispatchFunctionObject : public IDelayHandleItem
{
public:
	bool mIsClientDispose;       // 是否释放了资源
	EventDispatchDelegate mHandle;

public:
	EventDispatchFunctionObject();
	void setClientDispose();
	bool isClientDispose();
};

MY_END_NAMESPACE

#endif