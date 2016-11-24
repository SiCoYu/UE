#pragma once

#include "GameFramework/Actor.h"
#include "InterTest.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Interfaces_in_C%2B%2B
 */

UCLASS(config = Game)
class AInterTest : public AActor
{
	GENERATED_BODY()

public:
	AInterTest(const FObjectInitializer& ObjectInitializer);
	void test();
};