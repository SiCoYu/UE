#include "MyProject.h"
#include "AnimInstanceCppAndBlueprint.h"

//////////////////////////////////////////////////////////////////////////
// UVictoryAnimInstance

//This function is like PostInitAnimtree in UE3
void UAnimInstanceCppAndBlueprint::NativeInitializeAnimation()
{
	//Very Important Line
	Super::NativeInitializeAnimation();

	//Cache the owning pawn for use in Tick
	OwningPawn = TryGetPawnOwner();
}

//Tick
void UAnimInstanceCppAndBlueprint::NativeUpdateAnimation(float DeltaTimeX)
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