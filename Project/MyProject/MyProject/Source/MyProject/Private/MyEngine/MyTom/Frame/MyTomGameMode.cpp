#include "MyProject.h"
#include "MyFlyGameMode.h"
#include "MyFlyPawn.h"
#include "MyFlyPlayerController.h"

AMyFlyGameMode::AMyFlyGameMode()
{
	// set default pawn class to our flying pawn
	this->DefaultPawnClass = AMyFlyPawn::StaticClass();
	this->HUDClass = AHUD::StaticClass();
	this->PlayerControllerClass = AMyFlyPlayerController::StaticClass();
	this->GameStateClass = AGameState::StaticClass();
	this->PlayerStateClass = APlayerState::StaticClass();
	this->SpectatorClass = ASpectatorPawn::StaticClass();
}
