#include "MyProject.h"
#include "ResInsEventDispatch.h"

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

void ResInsEventDispatch::setInsGO(UObject* go)
{
	this->mInsGO = go;
}

UObject* ResInsEventDispatch::getInsGO()
{
	return this->mInsGO;
}

void ResInsEventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	if (this->mIsValid)
	{
		Super::dispatchEvent(dispatchObject);
	}
	else
	{
		//UtilApi.Destroy(mInsGO);
	}
}