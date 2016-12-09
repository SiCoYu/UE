#pragma once
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	TMapBase<int32, UClass*, false> PawnTypes;

public:
	AMyProjectGameMode(const FObjectInitializer& ObjectInitializer);
	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Every_Player
	UClass* GetDefaultPawnClassForController(AController* InController);

private:
	virtual void StartPlay();
	void TestUI();
};