#include "MyProject.h"
#include "EventDispatchFunctionObject.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE