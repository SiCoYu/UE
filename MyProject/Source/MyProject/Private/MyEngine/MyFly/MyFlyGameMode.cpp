#include "MyProject.h"
#include "AMyFlyGameMode.h"
#include "MyFlyPawn.h"

AAMyFlyGameMode::AAMyFlyGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AMyProjectPawn::StaticClass();
}
