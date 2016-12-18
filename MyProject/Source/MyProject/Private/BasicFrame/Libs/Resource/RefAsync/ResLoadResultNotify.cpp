#include "MyProject.h"
#include "ResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"

ResLoadResultNotify::ResLoadResultNotify()
{
	mResLoadState = new ResLoadState();
	mLoadResEventDispatch = new ResEventDispatch();
}

ResLoadResultNotify::~ResLoadResultNotify()
{
	delete mResLoadState;
	delete mLoadResEventDispatch;
}

ResLoadState* ResLoadResultNotify::getResLoadState()
{
	return mResLoadState;
}

void ResLoadResultNotify::setResLoadState(ResLoadState* value)
{
	mResLoadState = value;
}

ResEventDispatch* ResLoadResultNotify::getLoadResEventDispatch()
{
	return mLoadResEventDispatch;
}

void ResLoadResultNotify::setLoadResEventDispatch(ResEventDispatch* value)
{
	mLoadResEventDispatch = value;
}

void ResLoadResultNotify::onLoadEventHandle(IDispatchObject* dispObj)
{
	mLoadResEventDispatch->dispatchEvent(dispObj);
	mLoadResEventDispatch->clearEventHandle();
}

void ResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	mResLoadState->copyFrom(rhv->getResLoadState());
	mLoadResEventDispatch = rhv->getLoadResEventDispatch();
}