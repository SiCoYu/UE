#include "MyProject.h"
#include "MyPlayerState.h"

AMyPlayerState::AMyPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void AMyPlayerState::Reset()
{
	Super::Reset();
}

void AMyPlayerState::UnregisterPlayerWithSession()
{
	Super::UnregisterPlayerWithSession();
}

void AMyPlayerState::ClientInitialize(AController* InController)
{
	Super::ClientInitialize(InController);
}

void AMyPlayerState::CopyProperties(APlayerState* PlayerState)
{	
	Super::CopyProperties(PlayerState);
}