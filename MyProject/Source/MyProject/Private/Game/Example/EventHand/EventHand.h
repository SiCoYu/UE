#pragma once

#include "GameFramework/Actor.h"
#include "EventHand.generated.h"

/**
* @brief https://wiki.unrealengine.com/Event_handling
*/

UCLASS(config = Game)
class AEventHand : public AActor
{
	GENERATED_BODY()

public:
	AEventHand(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnOverlap(AActor* OtherActor);

	void addEventHandle();
};