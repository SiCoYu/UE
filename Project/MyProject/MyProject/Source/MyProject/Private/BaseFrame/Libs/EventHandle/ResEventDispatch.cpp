#include "MyProject.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ResEventDispatch, EventDispatch)

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