#pragma once

#include "MyPlayerStartBase.h"
#include "MyTPPlayerStart.generated.h"

UCLASS(config=Game)
class AMyTPPlayerStart : public AMyPlayerStartBase
{
	GENERATED_BODY()

public:
	AMyTPPlayerStart(const FObjectInitializer& ObjectInitializer);
	bool GetIsPlayerOnly();
};