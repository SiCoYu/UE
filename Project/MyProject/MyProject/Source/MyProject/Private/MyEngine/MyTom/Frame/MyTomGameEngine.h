#pragma once

#include "MyGameEngineBase.h"
#include "MyTomGameEngine.generated.h"

/**
 (1)
 UGameEngine ���� UGameInstance
 F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Engine\Private\GameEngine.cpp
 GameInstance = NewObject<UGameInstance>(this, GameInstanceClass);

 (2)
 UGameInstance ���� UWorld

 (3)
 UWorld ���� Level
 UWorld ���� ULocalPlayer �� APlayerController
 */

UCLASS()
class UMyTomGameEngine : public UMyGameEngineBase
{
	GENERATED_UCLASS_BODY()

	/* Hook up specific callbacks */
	virtual void Init(IEngineLoop* InEngineLoop);
};