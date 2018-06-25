#include "MyProject.h"
#include "MyTomAnimInstance.h"

UMyTomAnimInstance::UMyTomAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

//void UMyTomAnimInstance::testA()
//{
//
//}
//
//void UMyTomAnimInstance::NativeInitializeAnimation()
//{
//	//Very Important Line
//	Super::NativeInitializeAnimation();
//
//	//Cache the owning pawn for use in Tick
//	OwningPawn = TryGetPawnOwner();
//}
//
////Tick
//void UMyTomAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
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