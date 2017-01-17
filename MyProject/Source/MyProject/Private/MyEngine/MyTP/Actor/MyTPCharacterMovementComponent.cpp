#include "MyProject.h"
#include "MyTPCharacterMovementComponent.h"

//----------------------------------------------------------------------//
// UPawnMovementComponent
//----------------------------------------------------------------------//
UMyTPCharacterMovementComponent::UMyTPCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// https://answers.unrealengine.com/questions/160397/hot-reload-how-to-use.html
	//this->bOrientRotationToMovement = true;
}


float UMyCharacterMovement::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	return MaxSpeed;
}
