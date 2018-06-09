#ifndef __EventDispatchFunctionObject_H
#define __EventDispatchFunctionObject_H

#include "GObject.h"
#include "IDelayHandleItem.h"
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class EventDispatchFunctionObject : public GObject/*, public IDelayHandleItem*/
{
public:
	EventDispatchDelegate mHandle;

public:
	EventDispatchFunctionObject();
};

MY_END_NAMESPACE

#endif