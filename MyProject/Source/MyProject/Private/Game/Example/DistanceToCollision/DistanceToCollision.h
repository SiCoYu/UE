#pragma once

#include "GameFramework/Actor.h"
#include "DistanceToCollision.generated.h"

/**
* @brief https://wiki.unrealengine.com/Mesh_Collision,_Obtain_Closest_Point_on_Mesh_Surface_To_Other_Point
*/

UCLASS(config = Game)
class ADistanceToCollision : public AActor
{
	GENERATED_BODY()

public:
	ADistanceToCollision(const FObjectInitializer& ObjectInitializer);
	float DistanceOfActorToThisMeshSurface(AActor* TestActor, FVector& ClosestSurfacePoint) const;
};