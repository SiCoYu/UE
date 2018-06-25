#include "MyProject.h"
#include "MyTomCharacterMovementComponent.h"

//----------------------------------------------------------------------//
// UPawnMovementComponent
//----------------------------------------------------------------------//
UMyTomCharacterMovementComponent::UMyTomCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// https://answers.unrealengine.com/questions/160397/hot-reload-how-to-use.html
	this->bOrientRotationToMovement = true;
}

//float UMyTomCharacterMovementComponent::GetMaxSpeed() const
//{
//	float MaxSpeed = Super::GetMaxSpeed();
//
//	return MaxSpeed;
//}