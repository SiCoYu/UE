#include "MyProject.h"
#include "AddOnceAndCallOnceEventDispatch.h"

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