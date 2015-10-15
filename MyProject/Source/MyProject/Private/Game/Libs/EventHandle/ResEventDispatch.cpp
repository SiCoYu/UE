#include "MyProject.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"

ResEventDispatch::ResEventDispatch()
{

}

void ResEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	EventDispatch::dispatchEvent(dispatchObject);
	clearEventHandle();
}