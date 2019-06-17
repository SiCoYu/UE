#include "MyProject.h"
#include "CallOnceEventDispatch.h"
#include "IDispatchObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(CallOnceEventDispatch, EventDispatch)

CallOnceEventDispatch::CallOnceEventDispatch()
{

}

void CallOnceEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	Super::dispatchEvent(dispatchObject);
	this->clearEventHandle();
}

MY_END_NAMESPACE