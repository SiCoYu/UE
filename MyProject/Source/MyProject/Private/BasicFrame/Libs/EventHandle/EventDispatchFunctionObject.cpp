#include "MyProject.h"
#include "EventDispatchFunctionObject.h"

EventDispatchFunctionObject::EventDispatchFunctionObject()
{
	m_bClientDispose = false;
}

void EventDispatchFunctionObject::setClientDispose()
{
	m_bClientDispose = true;
}

bool EventDispatchFunctionObject::getClientDispose()
{
	return m_bClientDispose;
}