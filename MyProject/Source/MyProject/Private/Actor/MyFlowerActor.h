#pragma once

#include "GameFramework/Actor.h"
#include "MyFlowerActor.generated.h"

UCLASS(config = Game)
class AMyFlowerActor : public AActor
{
	GENERATED_BODY()

public:
	AMyFlowerActor(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaSeconds) override;
};