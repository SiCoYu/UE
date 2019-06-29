#pragma once

#include "MyGameModeBase.h"	// AGameModeBase
#include "GameFramework/GameMode.h"	// AGameModeBase
#include "Containers/Map.h"				// TMapBase
#include "GameFramework/Controller.h"	// AController
#include "UObject/Class.h"				// UClass
#include "UObject/UObjectGlobals.h"		// FObjectInitializer
#include "GameFramework/PlayerStart.h"
#include "Containers/Array.h"	// TArray
#include "MyTPGameMode.generated.h"

// AMyGameMode 必须继承 AGameModeBase，不能继承 AGameMode

/**
 如果继承 AGameModeBase ，不会调用 Actor::BeginPlay
 如果继承 AGameMode，就会调用 Actor::BeginPlay，调用如下
 (1)
 F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Engine\Private\GameMode.cpp
 // First fire BeginPlay, if we haven't already in waiting to start match
 GetWorldSettings()->NotifyBeginPlay();
 (2)
 void AWorldSettings::NotifyBeginPlay()
 {
	World->bBegunPlay = true;
 }
 F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Engine\Private\WorldSettings.cpp
 (3)
 bool bRunBeginPlay = !bDeferBeginPlayAndUpdateOverlaps && World->HasBegunPlay();
 if (bRunBeginPlay)
 {
	BeginPlay();
 }
 F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Engine\Private\Actor.cpp
 */

UCLASS(minimalapi)
//class AMyGameMode : public AGameModeBase
class AMyTPGameMode : public AMyGameModeBase
{
	GENERATED_BODY()

protected:
	//TMapBase<int32, UClass*, false> PawnTypes;
	TMap<int32, UClass> PawnTypes;

public:
	AMyTPGameMode(const FObjectInitializer& ObjectInitializer);

public:
	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Every_Player
	TArray<APlayerStart*> PlayerStarts;

	UClass* GetDefaultPawnClassForController(AController* InController);

	virtual void RestartPlayer(class AController* NewPlayer) override;
	AActor* ChoosePlayerStart(AController* Player);
	bool IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Controller);
	bool IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Controller);

private:
	virtual void StartPlay();
	void TestUi();
};