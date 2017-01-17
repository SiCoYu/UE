#include "MyProject.h"
#include "MyCharacterMovementComponentBase.h"

//----------------------------------------------------------------------//
// UPawnMovementComponent
//----------------------------------------------------------------------//
UMyCharacterMovementComponentBase::UMyCharacterMovementComponentBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// https://answers.unrealengine.com/questions/160397/hot-reload-how-to-use.html
	this->bOrientRotationToMovement = true;
}


float UMyCharacterMovementComponentBase::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	return MaxSpeed;
}
