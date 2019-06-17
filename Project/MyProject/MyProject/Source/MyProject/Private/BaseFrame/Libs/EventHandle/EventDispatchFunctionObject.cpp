#include "MyProject.h"
#include "EventDispatchFunctionObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(EventDispatchFunctionObject, GObject)

EventDispatchFunctionObject::EventDispatchFunctionObject()
{
	
}

void EventDispatchFunctionObject::init()
{

}

void EventDispatchFunctionObject::dispose()
{
	this->clear();
}

bool EventDispatchFunctionObject::operator ! ()
{
	return this->empty();
}

void EventDispatchFunctionObject::clear()
{
	this->clearFuncObject();
}

bool EventDispatchFunctionObject::empty()
{
	return this->mHandle.empty();
}

void EventDispatchFunctionObject::setFuncObject(EventDispatchDelegate handle)
{
	this->mHandle = handle;
}

void EventDispatchFunctionObject::clearFuncObject()
{
	this->mHandle.clear();
}

void EventDispatchFunctionObject::call(IDispatchObject* dispObj)
{
	this->mHandle(dispObj);
}

MY_END_NAMESPACE