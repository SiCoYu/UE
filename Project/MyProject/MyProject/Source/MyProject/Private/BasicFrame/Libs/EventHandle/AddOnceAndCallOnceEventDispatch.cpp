#include "MyProject.h"
#include "AddOnceAndCallOnceEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

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