#include "MyProject.h"
#include "DistanceToCollision.h"

ADistanceToCollision::ADistanceToCollision(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

float ADistanceToCollision::DistanceOfActorToThisMeshSurface(AActor* TestActor, FVector& ClosestSurfacePoint) const
{
	if (!TestActor) return;
	if (!TestActor->IsValidLowLevel()) return;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Dist of Actor to Surface, retrieve closest Surface Point to Actor
	return StaticMeshComponent->GetDistanceToCollision(
		TestActor->GetActorLocation(), ClosestSurfacePoint
		);
}