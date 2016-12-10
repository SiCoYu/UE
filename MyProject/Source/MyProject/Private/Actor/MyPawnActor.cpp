#include "MyProject.h"
#include "MyPawnActor.h"

AMyPawnActor::AMyPawnActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AMyPawnActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AMyProjectGameState* MyGameState = Cast<AMyProjectGameState>(GetWorld()->GetGameState());
	if (MyGameState)
	{

	}
}