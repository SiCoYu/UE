#include "MyProject.h"
#include "MyWorldSettings.h"
#include "MyFlyGameMode.h"

AMyFlyWorldSettings::AMyFlyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->DefaultGameMode = AMyFlyGameMode::StaticClass();
}