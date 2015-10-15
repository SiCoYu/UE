#include "MyProject.h"
#include "AddOnceAndCallOnceEventDispatch.h"

void AddOnceAndCallOnceEventDispatch::addEventHandle(EventDispatchDelegate handle)
{
	if (!existEventHandle(handle))
	{
		EventDispatch::addEventHandle(handle);
	}
}

void AddOnceAndCallOnceEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	EventDispatch::dispatchEvent(dispatchObject);
	clearEventHandle();
}