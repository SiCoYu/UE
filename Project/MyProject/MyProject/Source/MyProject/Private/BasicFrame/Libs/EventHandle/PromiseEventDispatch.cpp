#include "MyProject.h"
#include "PromiseEventDispatch.h"
#include "IDispatchObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PromiseEventDispatch, AddOnceEventDispatch)

PromiseEventDispatch::PromiseEventDispatch()
{
	this->mEventState = -1;
	this->mIsValid = false;
}

void PromiseEventDispatch::setEventState(int value)
{
	this->mIsValid = true;
	this->mEventState = value;

	Super::dispatchEvent(nullptr);
}

void PromiseEventDispatch::clearEventState()
{
	this->mIsValid = false;
	this->mEventState = -1;
}

void PromiseEventDispatch::addEventHandle(
	EventDispatchDelegate handle
) 
{
	if (this->mIsValid && !handle.empty())
	{
		handle.call(nullptr);
	}

	Super::addEventHandle(handle);
}

MY_END_NAMESPACE