#pragma once

//#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// AGameModeBase ���ģʽ������� Actor �� BeginPlayer����Ϊ WorldSetting �е� BeginPlyer
UCLASS(minimalapi)
//class AMyGameModeBase : public AGameModeBase
class AMyGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
	AMyGameModeBase(const FObjectInitializer& ObjectInitializer);
};