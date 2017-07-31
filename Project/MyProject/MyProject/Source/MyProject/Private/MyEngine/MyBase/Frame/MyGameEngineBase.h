#pragma once

#include "Engine/GameEngine.h"
#include "MyGameEngineBase.generated.h"

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

 ����������
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameEngine=/Script/MyProject.MyTPGameEngine
 */

UCLASS()
class UMyGameEngineBase : public UGameEngine
{
	GENERATED_UCLASS_BODY()

public:
	/* Hook up specific callbacks */
	virtual void Init(IEngineLoop* InEngineLoop) override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;
};