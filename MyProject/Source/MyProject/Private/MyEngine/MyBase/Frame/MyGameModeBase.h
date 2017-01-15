#pragma once

#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// AGameModeBase 这个模式不会调用 Actor 的 BeginPlayer，因为 WorldSetting 中的 BeginPlyer
UCLASS(minimalapi)
class AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
};



