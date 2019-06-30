#pragma once

#include "MyGameModeBase.h"	// AGameModeBase
#include "GameFramework/GameMode.h"	// AGameModeBase
#include "MyOaGameMode.generated.h"

// minimalapi 不能在 Windows 下 导出 dll 符号
//UCLASS(minimalapi)
UCLASS()
class AMyOaGameMode : public AMyGameModeBase
{
	GENERATED_BODY()

public:
	AMyOaGameMode(const FObjectInitializer& ObjectInitializer);
};