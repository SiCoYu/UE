#include "MyProject.h"
#include "MyTomGameMode.h"
#include "MyFlyPawn.h"
#include "MyFlyPlayerController.h"

AMyTomGameMode::AMyTomGameMode()
{
	// set default pawn class to our flying pawn
	this->DefaultPawnClass = AMyFlyPawn::StaticClass();
	this->HUDClass = AHUD::StaticClass();
	this->PlayerControllerClass = AMyFlyPlayerController::StaticClass();
	this->GameStateClass = AGameState::StaticClass();
	this->PlayerStateClass = APlayerState::StaticClass();
	this->SpectatorClass = ASpectatorPawn::StaticClass();
}
