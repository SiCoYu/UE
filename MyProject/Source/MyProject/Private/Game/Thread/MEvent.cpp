#include "MyProject.h"
#include "MEvent.h"

MEvent::MEvent()
{
	m_event = FPlatformProcess::GetSynchEventFromPool(true);
}

MEvent::~MEvent()
{
	FPlatformProcess::ReturnSynchEventToPool(m_event);
	m_event = nullptr;
}

void MEvent::Wait()
{
	m_event->Wait(MAX_uint32);
}

void MEvent::Reset()
{
	m_event->Reset();
}

void MEvent::Set()
{
	return m_event->Trigger();
}