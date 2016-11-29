#include "MyProject.h"
#include "BlueprintImplementableEventPlayerController.h"

ABlueprintImplementableEventPlayerController::ABlueprintImplementableEventPlayerController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void ABlueprintImplementableEventPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//========================
	// 	BP Interface
	if (Health >= 50)
	{
		this->PlayerIsHealthyTick(Health);
	}
	//========================
}