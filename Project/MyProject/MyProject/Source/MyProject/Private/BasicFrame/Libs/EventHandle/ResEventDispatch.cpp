#include "MyProject.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"

ResEventDispatch::ResEventDispatch()
{

}

ResEventDispatch::~ResEventDispatch()
{

}

void ResEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	Super::dispatchEvent(dispatchObject);
	this->clearEventHandle();
}