#include "MyProject.h"
#include "MEvent.h"

MEvent::MEvent()
{
	mEvent = FPlatformProcess::GetSynchEventFromPool(true);
}

MEvent::~MEvent()
{
	FPlatformProcess::ReturnSynchEventToPool(mEvent);
	mEvent = nullptr;
}

void MEvent::Wait()
{
	mEvent->Wait(MAX_uint32);
}

void MEvent::Reset()
{
	mEvent->Reset();
}

void MEvent::Set()
{
	return mEvent->Trigger();
}

void MEvent::WaitOne()
{
	mEvent->Wait(MAX_uint32);
}