#include "MyProject.h"
#include "AnimateVertexPositionsBPFunctionLibrary.h"

UAnimateVertexPositionsBPFunctionLibrary::UAnimateVertexPositionsBPFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool UAnimateVertexPositionsBPFunctionLibrary::AnimatedVertex__GetAnimatedVertexLocations(
	USkeletalMeshComponent* Mesh,
	TArray<FVector>& Locations,
	bool PerformPawnVelocityCorrection
	) {
	if (!Mesh || !Mesh->SkeletalMesh)
	{
		return false;
	}

	//~~~~~~~~~~~~~
	Locations.Empty();
	//~~~~~~~~~~~~~

	Mesh->ComputeSkinnedPositions(Locations);

	FTransform ToWorld = Mesh->GetComponentTransform();
	FVector WorldLocation = ToWorld.GetLocation();

	//Pawn Velocity Correction
	UPawnMovementComponent* MovementComp = nullptr;
	if (PerformPawnVelocityCorrection)
	{
		APawn* Pawn = Cast<APawn>(Mesh->GetOwner());
		MovementComp = (Pawn) ? Pawn->GetMovementComponent() : NULL;
	}
	bool DoVelocityCorrection = PerformPawnVelocityCorrection && MovementComp;
	//Pawn Velocity Correction

	for (FVector& EachVertex : Locations)
	{
		EachVertex = WorldLocation + ToWorld.TransformVector(EachVertex);
		if (DoVelocityCorrection)
		{
			EachVertex += MovementComp->Velocity * FApp::GetDeltaTime();
		}
	}

	return true;
}