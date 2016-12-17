#include "MyProject.h"
#include "AMyHUD.h"
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

bool AMyPlayerState::UserChatRPC_Validate(const FSChatMsg& newmessage)
{
	return true;
}

void AMyPlayerState::UserChatRPC_Implementation(const FSChatMsg& newmessage)
{
	UserChat(newmessage);
}

bool AMyPlayerState::UserChat_Validate(const FSChatMsg& newmessage)
{
	return true;
}

void AMyPlayerState::UserChat_Implementation(const FSChatMsg& newmessage)
{
	APlayerController* MyCon;
	AMyHUD* MyHud;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		MyCon = Cast<APlayerController>(*Iterator);
		if (MyCon)
		{
			MyHud = Cast<AMyHUD>(MyCon->GetHUD());
			if (MyHud && MyHud->MyUIWidget.IsValid())
				MyHud->MyUIWidget->AddMessage(newmessage); // place the chat message on this player controller
		}
	}
}