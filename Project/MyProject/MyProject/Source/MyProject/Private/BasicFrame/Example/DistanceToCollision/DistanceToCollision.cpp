#include "MyProject.h"
#include "DistanceToCollision.h"

ADistanceToCollision::ADistanceToCollision(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

float ADistanceToCollision::DistanceOfActorToThisMeshSurface(AActor* TestActor, FVector& ClosestSurfacePoint) const
{
	if (!TestActor) return 0;
	if (!TestActor->IsValidLowLevel()) return 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//UStaticMeshComponent* StaticMeshComponent = this->GetComponentByClass<UStaticMeshComponent::StaticClass()>();
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(this->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	//Dist of Actor to Surface, retrieve closest Surface Point to Actor
	return StaticMeshComponent->GetDistanceToCollision(
		TestActor->GetActorLocation(), ClosestSurfacePoint
		);
}