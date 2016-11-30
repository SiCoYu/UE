#pragma once

#include "GameFramework/Actor.h"
#include "BlueprintNativeEventsActor.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Blueprints,_Empower_Your_Entire_Team_With_BlueprintNativeEvents
 */

UCLASS()
class ABlueprintNativeEventsActor : public AActor
{
	GENERATED_UCLASS_BODY()

	//Override in BP to extend the base C++ functionality!
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "JoyBall")
	float GetArmorRating() const;
};