#include "MyProject.h"
#include "MEvent.h"

MY_BEGIN_NAMESPACE(MyNS)

MEvent::MEvent()
{
	this->mEvent = FPlatformProcess::GetSynchEventFromPool(true);
}

MEvent::~MEvent()
{
	FPlatformProcess::ReturnSynchEventToPool(mEvent);
	this->mEvent = nullptr;
}

void MEvent::init()
{

}

void MEvent::dispose()
{

}

void MEvent::Wait()
{
	this->mEvent->Wait(MAX_uint32);
}

void MEvent::Reset()
{
	mEvent->Reset();
}

void MEvent::Set()
{
	return this->mEvent->Trigger();
}

void MEvent::WaitOne()
{
	this->mEvent->Wait(MAX_uint32);
}

MY_END_NAMESPACE