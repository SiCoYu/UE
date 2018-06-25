#pragma once

#include "MyPlayerStartBase.h"
#include "MyTomPlayerStart.generated.h"

UCLASS(config=Game)
class AMyTomPlayerStart : public AMyPlayerStartBase
{
	GENERATED_BODY()

public:
	AMyTomPlayerStart(const FObjectInitializer& ObjectInitializer);
	bool GetIsPlayerOnly();
};