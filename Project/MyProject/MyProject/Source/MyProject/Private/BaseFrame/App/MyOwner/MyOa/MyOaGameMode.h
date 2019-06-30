#pragma once

#include "MyGameModeBase.h"	// AGameModeBase
#include "GameFramework/GameMode.h"	// AGameModeBase
#include "MyOaGameMode.generated.h"

// minimalapi ������ Windows �� ���� dll ����
//UCLASS(minimalapi)
UCLASS()
class AMyOaGameMode : public AMyGameModeBase
{
	GENERATED_BODY()

public:
	AMyOaGameMode(const FObjectInitializer& ObjectInitializer);
};