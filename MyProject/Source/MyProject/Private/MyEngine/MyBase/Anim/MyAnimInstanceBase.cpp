#include "MyProject.h"
#include "MyAnimInstanceBase.h"

UMyAnimInstanceBase::UMyAnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UMyAnimInstanceBase::testA()
{

}

void UMyAnimInstanceBase::NativeInitializeAnimation()
{
	//Very Important Line
	Super::NativeInitializeAnimation();

	//Cache the owning pawn for use in Tick
	OwningPawn = TryGetPawnOwner();
}

//Tick
void UMyAnimInstanceBase::NativeUpdateAnimation(float DeltaTimeX)
{
	//Very Important Line
	Super::NativeUpdateAnimation(DeltaTimeX);

	//Always Check Pointers
	if (!OwningPawn)
	{
		return;
	}

	//Set whether moving or not
	IsMoving = (OwningPawn->GetVelocity().SizeSquared() > 25);
}