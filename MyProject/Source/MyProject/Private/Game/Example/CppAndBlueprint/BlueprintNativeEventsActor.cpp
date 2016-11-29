#include "MyProject.h"
#include "Logging/LogMacros.h"
//#include "LogMacro.h"
#include "BlueprintNativeEventsActor.h"

ABlueprintNativeEventsActor::ABlueprintNativeEventsActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

float ABlueprintNativeEventsActor::GetArmorRating_Implementation() const
{
	//remember to call super / parent function in BP!
	//V_LOG("C++ Happens First");
	return 100;
}