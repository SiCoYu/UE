#include "MyProject.h"
#include "MyTomWorldSettings.h"
#include "MyTomGameMode.h"
#include "GameFramework/GameModeBase.h"

AMyTomWorldSettings::AMyTomWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->DefaultGameMode = AMyTomGameMode::StaticClass();
}