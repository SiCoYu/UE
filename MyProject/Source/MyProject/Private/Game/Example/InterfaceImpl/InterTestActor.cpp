#include "MyProject.h"
#include "InterTestActor.h"
#include "ReactsToTimeOfDay.h"

AInterTestActor::AInterTestActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AInterTestActor::test()
{
	//Example: somewhere else in code we are trying to see if our object reacts to time of day

	//Some pointer is defined to any class inheriting from UObject
	UObject* pointerToAnyUObject = nullptr;

	//....
	IReactsToTimeOfDay* TheInterface = Cast<IReactsToTimeOfDay>(pointerToAnyUObject);
	if (TheInterface)
	{
		//Don't call your functions directly, use the 'Execute_' prefix
		//the Execute_ReactToHighNoon and Execute_ReactToMidnight are generated on compile
		//you may need to compile before these functions will appear
		TheInterface->Execute_ReactToHighNoon(pointerToAnyUObject);
		TheInterface->Execute_ReactToMidnight(pointerToAnyUObject);
	}

	//end of code segment
}