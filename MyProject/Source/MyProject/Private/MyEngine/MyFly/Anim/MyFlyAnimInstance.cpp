#include "MyProject.h"
#include "MyFlyAnimInstance.h"

UMyFlyAnimInstance::UMyFlyAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

//void UMyAnimInstance::testA()
//{
//
//}
//
//void UMyAnimInstance::NativeInitializeAnimation()
//{
//	//Very Important Line
//	Super::NativeInitializeAnimation();
//
//	//Cache the owning pawn for use in Tick
//	OwningPawn = TryGetPawnOwner();
//}
//
////Tick
//void UMyAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
//{
//	//Very Important Line
//	Super::NativeUpdateAnimation(DeltaTimeX);
//
//	//Always Check Pointers
//	if (!OwningPawn)
//	{
//		return;
//	}
//
//	//Set whether moving or not
//	IsMoving = (OwningPawn->GetVelocity().SizeSquared() > 25);
//}