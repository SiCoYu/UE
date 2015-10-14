#ifndef __AddOnceAndCallOnceEventDispatch_H
#define __AddOnceAndCallOnceEventDispatch_H

#include "EventDispatch.h"

class AddOnceAndCallOnceEventDispatch : public EventDispatch
{
public:
	virtual void addEventHandle(Action<IDispatchObject> handle) override;
	virtual void dispatchEvent(IDispatchObject dispatchObject) override;
};

#endif