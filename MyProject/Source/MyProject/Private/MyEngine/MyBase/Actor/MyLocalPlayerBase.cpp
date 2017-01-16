#include "MyProject.h"
#include "MyLocalPlayerBase.h"
//#include "MyGameInstanceBase.h"

UMyLocalPlayerBase::UMyLocalPlayerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyLocalPlayerBase::SetControllerId(int32 NewControllerId)
{
	Super::SetControllerId(NewControllerId);
}

UMyPersistentUser* UMyLocalPlayerBase::GetPersistentUser() const
{
	// if persistent data isn't loaded yet, load it
	if (PersistentUser == nullptr)
	{
		UMyLocalPlayerBase* const MutableThis = const_cast<UMyLocalPlayerBase*>(this);
		// casting away constness to enable caching implementation behavior
		MutableThis->LoadPersistentUser();
	}
	return PersistentUser;
}

void UMyLocalPlayerBase::LoadPersistentUser()
{
	FString SaveGameName = GetNickname();
}

FString UMyLocalPlayerBase::GetNickname() const
{
	FString UserNickName = Super::GetNickname();

	return UserNickName;
}
