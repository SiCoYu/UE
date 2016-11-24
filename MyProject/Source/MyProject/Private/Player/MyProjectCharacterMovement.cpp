#include "ShooterGame.h"
#include "Player/MyProjectCharacterMovement.h"

//----------------------------------------------------------------------//
// UPawnMovementComponent
//----------------------------------------------------------------------//
UMyProjectCharacterMovement::UMyProjectCharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


float UMyProjectCharacterMovement::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	return MaxSpeed;
}
