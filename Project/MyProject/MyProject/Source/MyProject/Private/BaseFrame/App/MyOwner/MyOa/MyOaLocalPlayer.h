// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyLocalPlayerBase.h"
#include "MyOaLocalPlayer.generated.h"

//UCLASS(config=Engine, transient)
UCLASS()
class UMyOaLocalPlayer : public UMyLocalPlayerBase
{
	GENERATED_UCLASS_BODY()

//public:
//
//	virtual void SetControllerId(int32 NewControllerId) override;
//
//	virtual FString GetNickname() const;
//
//	class UMyPersistentUser* GetPersistentUser() const;
//	
//	/** Initializes the PersistentUser */
//	void LoadPersistentUser();
//
//private:
//	/** Persistent user data stored between sessions (i.e. the user's savegame) */
//	UPROPERTY()
//	class UMyPersistentUser* PersistentUser;
};