#pragma once

#include "ReactsToTimeOfDay.h"
#include "GameFramework/Character.h"
#include "Frog.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Interfaces_in_C%2B%2B
 */

UCLASS()
class AFrog : public ACharacter, public IReactsToTimeOfDay
{
	GENERATED_BODY()
		/*
		... other AFrog properties and functions declared ...
		*/

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
		bool ReactToHighNoon();
	virtual bool ReactToHighNoon_Implementation() override;

};