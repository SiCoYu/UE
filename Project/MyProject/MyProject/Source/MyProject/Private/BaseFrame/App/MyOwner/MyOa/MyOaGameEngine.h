#pragma once

#include "MyGameEngineBase.h"
#include "MyOaGameEngine.generated.h"

/**
 (1)
 UGameEngine 创建 UGameInstance
 F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Engine\Private\GameEngine.cpp
 GameInstance = NewObject<UGameInstance>(this, GameInstanceClass);

 (2)
 UGameInstance 创建 UWorld

 (3)
 UWorld 创建 Level
 UWorld 创建 ULocalPlayer 和 APlayerController
 */

UCLASS()
class UMyOaGameEngine : public UMyGameEngineBase
{
	GENERATED_UCLASS_BODY()

	/* Hook up specific callbacks */
	virtual void Init(IEngineLoop* InEngineLoop);
};