#include "MyProject.h"
#include "EventDispatchFunctionObject.h"

EventDispatchFunctionObject::EventDispatchFunctionObject()
{
	mIsClientDispose = false;
}

void EventDispatchFunctionObject::setClientDispose()
{
	mIsClientDispose = true;
}

bool EventDispatchFunctionObject::isClientDispose()
{
	return mIsClientDispose;
}