#include "MyProject.h"
#include "EventDispatchFunctionObject.h"

MY_BEGIN_NAMESPACE(MyNS)

EventDispatchFunctionObject::EventDispatchFunctionObject()
{
	this->mIsClientDispose = false;
}

void EventDispatchFunctionObject::setClientDispose(bool isDispose)
{
	this->mIsClientDispose = isDispose;
}

bool EventDispatchFunctionObject::isClientDispose()
{
	return this->mIsClientDispose;
}

MY_END_NAMESPACE