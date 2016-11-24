// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyProjectPersistentUser.h"
#include "MyProjectLocalPlayer.generated.h"

UCLASS(config=Engine, transient)
class UMyProjectLocalPlayer : public ULocalPlayer
{
	GENERATED_UCLASS_BODY()

public:

	virtual void SetControllerId(int32 NewControllerId) override;

	virtual FString GetNickname() const;

	class UShooterPersistentUser* GetPersistentUser() const;
	
	/** Initializes the PersistentUser */
	void LoadPersistentUser();

private:
	/** Persistent user data stored between sessions (i.e. the user's savegame) */
	UPROPERTY()
	class UShooterPersistentUser* PersistentUser;
};



