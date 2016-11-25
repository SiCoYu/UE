#pragma once

#include "GameFramework/Actor.h"
#include "CoordinateMappingActor.generated.h"

/**
* @brief https://wiki.unrealengine.com/Coordinate_mapping_from_leap_motion_to_unreal_world
*/

UCLASS(config = Game)
class ACoordinateMappingActor : public AActor
{
	GENERATED_BODY()

public:
	void UpdateBonesOne(float DeltaSeconds);
	void UpdateBonesTwo(float DeltaSeconds);
};