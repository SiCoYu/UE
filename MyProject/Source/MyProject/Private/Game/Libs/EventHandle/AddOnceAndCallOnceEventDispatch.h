#ifndef __AddOnceAndCallOnceEventDispatch_H
#define __AddOnceAndCallOnceEventDispatch_H

#include "EventDispatch.h"
#include "EventDispatchDelegate.h"

class AddOnceAndCallOnceEventDispatch : public EventDispatch
{
public:
	virtual void addEventHandle(EventDispatchDelegate handle) override;
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

#endif