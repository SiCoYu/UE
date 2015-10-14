#include "MyProject.h"
#include "ResEventDispatch.h"

ResEventDispatch::ResEventDispatch()
{

}

void ResEventDispatch::dispatchEvent(IDispatchObject dispatchObject)
{
	EventDispatch::dispatchEvent(dispatchObject);
	clearEventHandle();
}