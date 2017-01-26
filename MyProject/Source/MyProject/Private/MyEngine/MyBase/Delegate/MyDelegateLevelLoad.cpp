#include "MyProject.h"
#include "MyDelegateLevelLoad.h"

UMyDelegateLevelLoad::UMyDelegateLevelLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UMyDelegateLevelLoad::onLevelLoaded()
{
	this->mMyDelegateBaseHandle.Execute(nullptr);
}