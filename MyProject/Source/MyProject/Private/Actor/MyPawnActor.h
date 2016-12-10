#pragma once

#include "GameFramework/Actor.h"
#include "MyPawnActor.generated.h"

UCLASS(config = Game)
class AMyPawnActor : public AActor
{
	GENERATED_BODY()

public:
	AMyPawnActor(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaSeconds) override;
};