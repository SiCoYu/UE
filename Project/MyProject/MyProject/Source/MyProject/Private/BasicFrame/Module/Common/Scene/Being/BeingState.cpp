#include "MyProject.h"
#include "BeingState.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

float AnimaionEventTimeLine::onStartAnimEvent = 0.04f;

std::string AnimaionEventName::onStartAnimEvent = "onStartAnimEvent";

std::string AnimaionName::eBSIdle = "idle";

BeingActId BeingStateTransit::convState2Act(BeingState state)
{
	return BeingActId.eActIdle;
}

MY_END_NAMESPACE