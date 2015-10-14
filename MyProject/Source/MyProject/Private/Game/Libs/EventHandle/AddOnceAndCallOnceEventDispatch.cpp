#include "MyProject.h"
#include "AddOnceAndCallOnceEventDispatch.h"

void AddOnceAndCallOnceEventDispatch::addEventHandle(Action<IDispatchObject> handle)
{
	if (!existEventHandle(handle))
	{
		base.addEventHandle(handle);
	}
}

void AddOnceAndCallOnceEventDispatch::dispatchEvent(IDispatchObject dispatchObject)
{
	base.dispatchEvent(dispatchObject);
	clearEventHandle();
}