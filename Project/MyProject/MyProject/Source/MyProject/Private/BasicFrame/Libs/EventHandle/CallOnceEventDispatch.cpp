#include "MyProject.h"
#include "CallOnceEventDispatch.h"
#include "IDispatchObject.h"

MY_BEGIN_NAMESPACE(MyNS)

CallOnceEventDispatch::CallOnceEventDispatch()
{

}

void CallOnceEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	Super::dispatchEvent(dispatchObject);
	this->clearEventHandle();
}

MY_END_NAMESPACE