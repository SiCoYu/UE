#include "MyProject.h"
#include "MyTomGameMode.h"
#include "MyTomPawn.h"
#include "MyTomPlayerController.h"

AMyTomGameMode::AMyTomGameMode()
{
	// set default pawn class to our flying pawn
	this->DefaultPawnClass = AMyTomPawn::StaticClass();
	this->HUDClass = AHUD::StaticClass();
	this->PlayerControllerClass = AMyTomPlayerController::StaticClass();
	this->GameStateClass = AGameState::StaticClass();
	this->PlayerStateClass = APlayerState::StaticClass();
	this->SpectatorClass = ASpectatorPawn::StaticClass();
}
