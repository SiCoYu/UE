#pragma once
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode(const FObjectInitializer& ObjectInitializer);

private:
	virtual void StartPlay();
	void TestUI();
};