#include "MyProject.h"
#include "Player/MyLocalPlayer.h"
#include "MyGameInstanceBase.h"

UMyLocalPlayer::UMyLocalPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyLocalPlayer::SetControllerId(int32 NewControllerId)
{
	Super::SetControllerId(NewControllerId);
}

UMyPersistentUser* UMyLocalPlayer::GetPersistentUser() const
{
	// if persistent data isn't loaded yet, load it
	if (PersistentUser == nullptr)
	{
		UMyLocalPlayer* const MutableThis = const_cast<UMyLocalPlayer*>(this);
		// casting away constness to enable caching implementation behavior
		MutableThis->LoadPersistentUser();
	}
	return PersistentUser;
}

void UMyLocalPlayer::LoadPersistentUser()
{
	FString SaveGameName = GetNickname();
}

FString UMyLocalPlayer::GetNickname() const
{
	FString UserNickName = Super::GetNickname();

	return UserNickName;
}
