// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "MySaveGameBase.h"
#include "Engine/LocalPlayer.h"
#include "MyLocalPlayerBase.generated.h"

class UMySaveGameBase;

/**
 @brief 
 在这里设置
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 LocalPlayerClassName=/Script/MyProject.MyTPLocalPlayer
 */

//UCLASS(config=Engine, transient)
UCLASS()
class UMyLocalPlayerBase : public ULocalPlayer
{
	GENERATED_UCLASS_BODY()

public:

	virtual void SetControllerId(int32 NewControllerId) override;

	virtual FString GetNickname() const;

	class UMyPersistentUser* GetPersistentUser() const;
	
	/** Initializes the PersistentUser */
	void LoadPersistentUser();

private:
	/** Persistent user data stored between sessions (i.e. the user's savegame) */
	UPROPERTY()
	class UMySaveGameBase* PersistentUser;
};