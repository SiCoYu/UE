#ifndef __ResEventDispatch_H
#define __ResEventDispatch_H

#include "EventDispatch.h"

class ResEventDispatch : public EventDispatch
{
public:
	ResEventDispatch();
	virtual void dispatchEvent(IDispatchObject dispatchObject) override
};

#endif