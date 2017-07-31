#include "MyProject.h"
#include "EventDispatchFunctionObject.h"

EventDispatchFunctionObject::EventDispatchFunctionObject()
{
	this->mIsClientDispose = false;
}

void EventDispatchFunctionObject::setClientDispose()
{
	this->mIsClientDispose = true;
}

bool EventDispatchFunctionObject::isClientDispose()
{
	return this->mIsClientDispose;
}