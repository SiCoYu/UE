#include "MyProject.h"
#include "MyOaLocalPlayer.h"
//#include "MyGameInstanceBase.h"

UMyOaLocalPlayer::UMyOaLocalPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//void UMyLocalPlayer::SetControllerId(int32 NewControllerId)
//{
//	Super::SetControllerId(NewControllerId);
//}
//
//UMyPersistentUser* UMyTomLocalPlayer::GetPersistentUser() const
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
//void UMyTomLocalPlayer::LoadPersistentUser()
//{
//	FString SaveGameName = GetNickname();
//}
//
//FString UMyTomLocalPlayer::GetNickname() const
//{
//	FString UserNickName = Super::GetNickname();
//
//	return UserNickName;
//}
