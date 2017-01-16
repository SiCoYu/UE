#pragma once

#include "GameFramework/PlayerStart.h"
#include "MyPlayerStartBase.generated.h"

UCLASS(config=Game)
class AMyPlayerStartBase : public APlayerStart
{
	GENERATED_BODY()

public:
	//AMyPlayerStartBase(const FObjectInitializer& ObjectInitializer);
	bool GetIsPlayerOnly();
};