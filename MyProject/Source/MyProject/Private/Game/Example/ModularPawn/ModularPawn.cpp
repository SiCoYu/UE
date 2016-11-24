#include "MyProject.h"
#include "ModularPawn.h"

FName AModularPawn::BodyComponentName(TEXT("CharacterBody0"));
FName AModularPawn::LegsComponentName(TEXT("CharacterLegs0"));

AModularPawn::AModularPawn(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	static FName CollisionProfileName(TEXT("IgnoreOnlyPawn"));

	Body = PCIP.CreateOptionalDefaultSubobject<USkeletalMeshComponent>(this, AMyCharacter::BodyComponentName);
	if (Body)
	{
		Body->AlwaysLoadOnClient = true;
		Body->AlwaysLoadOnServer = true;
		Body->bOwnerNoSee = false;
		Body->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Body->bCastDynamicShadow = true;
		Body->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Body->bChartDistanceFactor = true;
		Body->SetCollisionProfileName(CollisionProfileName);
		Body->bGenerateOverlapEvents = false;

		// Mesh acts as the head, as well as the parent for both animation and attachment.
		Body->AttachParent = Mesh;
		Body->SetMasterPoseComponent(Mesh);

		Components.Add(Body);
	}

	Legs = PCIP.CreateOptionalDefaultSubobject<USkeletalMeshComponent>(this, AMyCharacter::LegsComponentName);
	if (Legs)
	{
		Legs->AlwaysLoadOnClient = true;
		Legs->AlwaysLoadOnServer = true;
		Legs->bOwnerNoSee = false;
		Legs->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Legs->bCastDynamicShadow = true;
		Legs->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Legs->bChartDistanceFactor = true;
		Legs->SetCollisionProfileName(CollisionProfileName);
		Legs->bGenerateOverlapEvents = false;

		// Mesh acts as the head, as well as the parent for both animation and attachment.
		Legs->AttachParent = Mesh;
		Legs->SetMasterPoseComponent(Mesh);

		Components.Add(Legs);
	}
}