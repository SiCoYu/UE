#include "MyProject.h"
#include "CallFuncObjectBase.h"
#include "IDispatchObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(CallFuncObjectBase, GObject)

CallFuncObjectBase::CallFuncObjectBase()
{

}

void CallFuncObjectBase::init()
{

}

void CallFuncObjectBase::dispose()
{
	this->clear();
}

void CallFuncObjectBase::clear()
{
	this->clearEventHandle();
}

bool CallFuncObjectBase::isValid()
{
	return false;
}

void CallFuncObjectBase::setEventHandle(EventDispatchDelegate handle)
{
	this->mHandle = handle;
}

void CallFuncObjectBase::clearEventHandle()
{
	this->mHandle = nullptr;
}

void CallFuncObjectBase::dispatchEvent(IDispatchObject* dispObj)
{
	this->mHandle(dispObj);
}

MY_END_NAMESPACE