#ifndef __EventDispatchFunctionObject_H
#define __EventDispatchFunctionObject_H

#include "GObject.h"
#include "IDelayHandleItem.h"
#include "EventDispatchDelegate.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class EventDispatchFunctionObject : public GObject/*, public IDelayHandleItem*/
{
	M_DECLARE_CLASS(EventDispatchFunctionObject, GObject)

public:
	EventDispatchDelegate mHandle;

public:
	EventDispatchFunctionObject();

	void init();
	void dispose();

	bool operator ! ();

	virtual void clear();
	virtual void clearFuncObject();

	virtual bool empty();

	virtual void setFuncObject(EventDispatchDelegate handle);
	virtual void call(IDispatchObject* dispObj);
};

MY_END_NAMESPACE

#endif