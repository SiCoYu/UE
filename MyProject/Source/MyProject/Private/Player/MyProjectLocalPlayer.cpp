#include "MyProject.h"
#include "Player/MyProjectLocalPlayer.h"
#include "MyProjectGameInstance.h"

UMyProjectLocalPlayer::UMyProjectLocalPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UMyProjectPersistentUser* UMyProjectLocalPlayer::GetPersistentUser() const
{
	// if persistent data isn't loaded yet, load it
	if (PersistentUser == nullptr)
	{
		UMyProjectLocalPlayer* const MutableThis = const_cast<UMyProjectLocalPlayer*>(this);
		// casting away constness to enable caching implementation behavior
		MutableThis->LoadPersistentUser();
	}
	return PersistentUser;
}

void UMyProjectLocalPlayer::LoadPersistentUser()
{
	FString SaveGameName = GetNickname();
}

FString UMyProjectLocalPlayer::GetNickname() const
{
	FString UserNickName = Super::GetNickname();

	return UserNickName;
}
