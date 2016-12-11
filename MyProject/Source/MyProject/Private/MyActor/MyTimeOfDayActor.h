#pragma once

#include "GameFramework/Actor.h"
#include "MyTimeOfDayActor.generated.h"

/**
* @brief https://wiki.unrealengine.com/Survival_Sample_Game:_Section_4
*/

UCLASS(config = Game)
class AMyTimeOfDayActor : public AActor
{
	GENERATED_BODY()

public:
	AMyTimeOfDayActor(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaSeconds) override;
};