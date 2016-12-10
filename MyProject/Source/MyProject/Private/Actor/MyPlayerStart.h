#pragma once

#include "GameFramework/PlayerStart.h"
#include "MyPlayerStart.generated.h"

UCLASS(config = Game)
class AMyPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	AMyPlayerStart(const FObjectInitializer& ObjectInitializer);

	bool GetIsPlayerOnly();
};