#include "MyProject.h"
#include "ResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "IDispatchObject.h"

ResLoadResultNotify::ResLoadResultNotify()
{
	m_resLoadState = new ResLoadState();
	m_loadResEventDispatch = new ResEventDispatch();
}

ResLoadResultNotify::~ResLoadResultNotify()
{
	delete m_resLoadState;
	delete m_loadResEventDispatch;
}

ResLoadState* ResLoadResultNotify::getResLoadState()
{
	return m_resLoadState;
}

void ResLoadResultNotify::setResLoadState(ResLoadState* value)
{
	m_resLoadState = value;
}

ResEventDispatch* ResLoadResultNotify::getLoadResEventDispatch()
{
	return m_loadResEventDispatch;
}

void ResLoadResultNotify::setLoadResEventDispatch(ResEventDispatch* value)
{
	m_loadResEventDispatch = value;
}

void ResLoadResultNotify::onLoadEventHandle(IDispatchObject* dispObj)
{
	m_loadResEventDispatch->dispatchEvent(dispObj);
	m_loadResEventDispatch->clearEventHandle();
}

void ResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	m_resLoadState->copyFrom(rhv->getResLoadState());
	m_loadResEventDispatch = rhv->getLoadResEventDispatch();
}