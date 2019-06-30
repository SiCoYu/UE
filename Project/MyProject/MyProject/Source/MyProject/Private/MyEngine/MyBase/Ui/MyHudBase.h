#pragma once

#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "MyHudBase.generated.h"

UCLASS()
class AMyHudBase : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	/** Main HUD update loop. */
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

protected:
	virtual void PostInitializeComponents() override; // All game elements are created, add our chat box
};