#include "MyProject.h"
#include "MyFlyCharacterMovementComponent.h"

//----------------------------------------------------------------------//
// UPawnMovementComponent
//----------------------------------------------------------------------//
UMyFlyCharacterMovementComponent::UMyFlyCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// https://answers.unrealengine.com/questions/160397/hot-reload-how-to-use.html
	this->bOrientRotationToMovement = true;
}

//float UMyFlyCharacterMovementComponent::GetMaxSpeed() const
//{
//	float MaxSpeed = Super::GetMaxSpeed();
//
//	return MaxSpeed;
//}