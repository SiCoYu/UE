#pragma once

#include "GameFramework/GameModeBase.h"	// AGameModeBase
#include "Containers/Map.h"				// TMapBase
#include "GameFramework/Controller.h"	// AController
#include "UObject/Class.h"				// UClass
#include "UObject/UObjectGlobals.h"		// FObjectInitializer
#include "GameFramework/PlayerStart.h"
#include "Containers/Array.h"	// TArray
#include "MyGameMode.generated.h"

// AMyGameMode ±ØÐë¼Ì³Ð AGameModeBase£¬²»ÄÜ¼Ì³Ð AGameMode

UCLASS(minimalapi)
class AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	//TMapBase<int32, UClass*, false> PawnTypes;
	TMap<int32, UClass> PawnTypes;

public:
	AMyGameMode(const FObjectInitializer& ObjectInitializer);

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
	void TestUI();
};