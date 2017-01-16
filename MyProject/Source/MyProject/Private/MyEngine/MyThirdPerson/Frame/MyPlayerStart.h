#pragma once

#include "MyPlayerStartBase.h"
#include "MyPlayerStart.generated.h"

UCLASS(config=Game)
class AMyPlayerStart : public AMyPlayerStartBase
{
	GENERATED_BODY()

public:
	AMyPlayerStart(const FObjectInitializer& ObjectInitializer);
	bool GetIsPlayerOnly();
};