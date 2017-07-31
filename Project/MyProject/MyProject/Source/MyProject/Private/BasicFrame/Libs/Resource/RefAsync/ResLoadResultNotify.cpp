#include "MyProject.h"
#include "ResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"

ResLoadResultNotify::ResLoadResultNotify()
{
	this->mResLoadState = new ResLoadState();
	this->mLoadResEventDispatch = new ResEventDispatch();
}

ResLoadResultNotify::~ResLoadResultNotify()
{
	delete this->mResLoadState;
	delete this->mLoadResEventDispatch;
}

ResLoadState* ResLoadResultNotify::getResLoadState()
{
	return this->mResLoadState;
}

void ResLoadResultNotify::setResLoadState(ResLoadState* value)
{
	this->mResLoadState = value;
}

ResEventDispatch* ResLoadResultNotify::getLoadResEventDispatch()
{
	return this->mLoadResEventDispatch;
}

void ResLoadResultNotify::setLoadResEventDispatch(ResEventDispatch* value)
{
	this->mLoadResEventDispatch = value;
}

void ResLoadResultNotify::onLoadEventHandle(IDispatchObject* dispObj)
{
	this->mLoadResEventDispatch->dispatchEvent(dispObj);
	this->mLoadResEventDispatch->clearEventHandle();
}

void ResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	this->mResLoadState->copyFrom(rhv->getResLoadState());
	this->mLoadResEventDispatch = rhv->getLoadResEventDispatch();
}