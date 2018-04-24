#include "MyProject.h"
#include "AnimateVertexPositionsBPFunctionLibrary.h"

UAnimateVertexPositionsBPFunctionLibrary::UAnimateVertexPositionsBPFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

bool UAnimateVertexPositionsBPFunctionLibrary::AnimatedVertex__GetAnimatedVertexLocations(
	USkeletalMeshComponent* Mesh,
	TArray<FVector>& Locations, 
	TArray<FMatrix>& CachedRefToLocals, 
	const FSkeletalMeshLODRenderData& Model, 
	FSkinWeightVertexBuffer& SkinWeightBuffer, 
	bool PerformPawnVelocityCorrection
	) {
	if (!Mesh || !Mesh->SkeletalMesh)
	{
		return false;
	}

	//~~~~~~~~~~~~~
	Locations.Empty();
	//~~~~~~~~~~~~~

	// UE 4.19.1 error C2660: 'USkeletalMeshComponent::ComputeSkinnedPositions': function does not take 1 arguments
	//Mesh->ComputeSkinnedPositions(Locations);
	USkeletalMeshComponent::ComputeSkinnedPositions(Mesh, Locations, CachedRefToLocals, Model, SkinWeightBuffer);

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