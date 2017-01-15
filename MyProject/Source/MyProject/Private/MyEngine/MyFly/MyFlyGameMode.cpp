#include "MyProject.h"
#include "MyFlyGameMode.h"
#include "MyFlyPawn.h"

AMyFlyGameMode::AMyFlyGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AMyProjectPawn::StaticClass();
}
