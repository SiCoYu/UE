#pragma once

#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS(config=Game)
class ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem(const FObjectInitializer& ObjectInitializer);
};