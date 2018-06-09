#include "MyProject.h"
#include "EventDispatchFunctionObject.h"

MY_BEGIN_NAMESPACE(MyNS)

EventDispatchFunctionObject::EventDispatchFunctionObject()
{
	this->mIsClientDispose = false;
}

MY_END_NAMESPACE