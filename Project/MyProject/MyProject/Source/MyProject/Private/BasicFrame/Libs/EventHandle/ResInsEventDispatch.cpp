#include "MyProject.h"
#include "ResInsEventDispatch.h"
#include "UtilSysLibWrap.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ResInsEventDispatch, EventDispatch)

ResInsEventDispatch::ResInsEventDispatch()
{
	this->mIsValid = true;
}

void ResInsEventDispatch::setIsValid(bool value)
{
	this->mIsValid = value;
}

bool ResInsEventDispatch::getIsValid()
{
	return this->mIsValid;
}

void ResInsEventDispatch::setInsActor(AActor* go)
{
	this->mInsActor = go;
}

AActor* ResInsEventDispatch::getInsActor()
{
	return this->mInsActor;
}

void ResInsEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	if (this->mIsValid)
	{
		Super::dispatchEvent(dispatchObject);
	}
	else
	{
		UtilSysLibWrap::Destroy(this->mInsActor);
	}
}

MY_END_NAMESPACE