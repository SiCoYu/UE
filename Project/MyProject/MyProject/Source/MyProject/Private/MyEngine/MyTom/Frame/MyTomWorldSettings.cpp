#include "MyProject.h"
#include "MyFlyWorldSettings.h"
#include "MyFlyGameMode.h"
#include "GameFramework/GameModeBase.h"

AMyFlyWorldSettings::AMyFlyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->DefaultGameMode = AMyFlyGameMode::StaticClass();
}