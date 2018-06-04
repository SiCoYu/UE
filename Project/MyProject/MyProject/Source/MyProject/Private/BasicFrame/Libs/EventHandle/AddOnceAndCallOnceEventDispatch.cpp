#include "MyProject.h"
#include "AddOnceAndCallOnceEventDispatch.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AddOnceAndCallOnceEventDispatch, EventDispatch)

void AddOnceAndCallOnceEventDispatch::addEventHandle(EventDispatchDelegate handle)
{
	if (!this->isExistEventHandle(handle))
	{
		Super::addEventHandle(handle);
	}
}

void AddOnceAndCallOnceEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	Super::dispatchEvent(dispatchObject);
	this->clearEventHandle();
}

MY_END_NAMESPACE