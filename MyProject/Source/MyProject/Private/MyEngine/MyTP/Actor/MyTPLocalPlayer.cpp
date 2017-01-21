#include "MyProject.h"
#include "MyTPLocalPlayer.h"
//#include "MyGameInstanceBase.h"

UMyTPLocalPlayer::UMyTPLocalPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//void UMyTPLocalPlayer::SetControllerId(int32 NewControllerId)
//{
//	Super::SetControllerId(NewControllerId);
//}
//
//UMyPersistentUser* UMyTPLocalPlayer::GetPersistentUser() const
//{
//	// if persistent data isn't loaded yet, load it
//	if (PersistentUser == nullptr)
//	{
//		UMyLocalPlayer* const MutableThis = const_cast<UMyLocalPlayer*>(this);
//		// casting away constness to enable caching implementation behavior
//		MutableThis->LoadPersistentUser();
//	}
//	return PersistentUser;
//}
//
//void UMyTPLocalPlayer::LoadPersistentUser()
//{
//	FString SaveGameName = GetNickname();
//}
//
//FString UMyTPLocalPlayer::GetNickname() const
//{
//	FString UserNickName = Super::GetNickname();
//
//	return UserNickName;
//}
