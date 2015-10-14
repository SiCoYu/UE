#include "MyProject.h"
#include "CallOnceEventDispatch.h"

CallOnceEventDispatch::CallOnceEventDispatch()
{

}

void CallOnceEventDispatch::dispatchEvent(IDispatchObject dispatchObject)
{
	base.dispatchEvent(dispatchObject);
	clearEventHandle();
}