#pragma once

#include "ReactsToTimeOfDay.h"
#include "Animation/SkeletalMeshActor.h"
#include "Flower.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Interfaces_in_C%2B%2B
 */

UCLASS()
class AFlower : public ASkeletalMeshActor, public IReactsToTimeOfDay
{
	GENERATED_BODY()

public:
	/*
	... other AFlower properties and functions declared ...
	*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
		bool ReactToHighNoon();
	virtual bool ReactToHighNoon_Implementation() override;
};