#include "MyProject.h"
#include "MyProjectPlayerState.h"

AMyProjectPlayerState::AMyProjectPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void AMyProjectPlayerState::Reset()
{
	Super::Reset();
}

void AMyProjectPlayerState::UnregisterPlayerWithSession()
{
	Super::UnregisterPlayerWithSession();
}

void AMyProjectPlayerState::ClientInitialize(AController* InController)
{
	Super::ClientInitialize(InController);
}


void AMyProjectPlayerState::CopyProperties(APlayerState* PlayerState)
{	
	Super::CopyProperties(PlayerState);
}