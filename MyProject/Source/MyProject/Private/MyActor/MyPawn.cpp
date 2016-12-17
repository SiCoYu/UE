#include "MyProject.h"
#include "MyGameState.h"
#include "MyPawn.h"

AMyPawn::AMyPawn(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AMyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AMyGameState* MyGameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	if (MyGameState)
	{

	}
}

void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponentParam)
{
	Super::SetupPlayerInputComponent(InputComponentParam);

	//InputComponentParam->BindAction("ZoomIn", IE_Pressed, this, &AMyActor::CameraZoomIn);
	//InputComponentParam->BindAction("ZoomOut", IE_Pressed, this, &AMyActor::CameraZoomOut);
}