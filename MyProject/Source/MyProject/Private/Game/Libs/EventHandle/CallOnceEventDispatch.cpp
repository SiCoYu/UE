#include "MyProject.h"
#include "CallOnceEventDispatch.h"
#include "IDispatchObject.h"

CallOnceEventDispatch::CallOnceEventDispatch()
{

}

void CallOnceEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	EventDispatch::dispatchEvent(dispatchObject);
	clearEventHandle();
}