#pragma once

#include "GameFramework/Actor.h"
#include "InterTestActor.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Interfaces_in_C%2B%2B
 */

UCLASS(config = Game)
class AInterTestActor : public AActor
{
	GENERATED_BODY()

public:
	AInterTestActor(const FObjectInitializer& ObjectInitializer);
	void test();
};