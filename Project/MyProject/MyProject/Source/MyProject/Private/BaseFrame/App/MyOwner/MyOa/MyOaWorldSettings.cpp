#include "MyProject.h"
#include "MyOaWorldSettings.h"
#include "MyOaGameMode.h"
#include "GameFramework/GameModeBase.h"

AMyOaWorldSettings::AMyOaWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->DefaultGameMode = AMyOaGameMode::StaticClass();
}