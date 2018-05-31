#include "MyProject.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE