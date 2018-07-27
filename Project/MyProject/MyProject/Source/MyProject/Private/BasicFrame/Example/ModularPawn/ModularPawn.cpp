#include "MyProject.h"
#include "ModularPawn.h"

FName AModularPawn::BodyComponentName(TEXT("CharacterBody0"));
FName AModularPawn::LegsComponentName(TEXT("CharacterLegs0"));

AModularPawn::AModularPawn(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	static FName CollisionProfileName(TEXT("IgnoreOnlyPawn"));

	Body = PCIP.CreateOptionalDefaultSubobject<USkeletalMeshComponent>(this, AModularPawn::BodyComponentName);
	if (Body)
	{
		Body->AlwaysLoadOnClient = true;
		Body->AlwaysLoadOnServer = true;
		Body->bOwnerNoSee = false;
		Body->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Body->bCastDynamicShadow = true;
		Body->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		// USkinnedMeshComponent::bChartDistanceFactor': bChartDistanceFactor is no longer useful, please remove references to it Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//Body->bChartDistanceFactor = true;
		Body->SetCollisionProfileName(CollisionProfileName);
		// UE 4.20 error C2248 : 'UPrimitiveComponent::bGenerateOverlapEvents' : cannot access private member declared in class 'UPrimitiveComponent'
		//Body->bGenerateOverlapEvents = false;
		Body->SetGenerateOverlapEvents(false);

		// Mesh acts as the head, as well as the parent for both animation and attachment.
		//Body->AttachParent = Mesh;
		Body->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		//Body->SetMasterPoseComponent(Mesh);
		Body->SetMasterPoseComponent(this->GetMesh());

		//Components.Add(Body);
	}

	Legs = PCIP.CreateOptionalDefaultSubobject<USkeletalMeshComponent>(this, AModularPawn::LegsComponentName);
	if (Legs)
	{
		Legs->AlwaysLoadOnClient = true;
		Legs->AlwaysLoadOnServer = true;
		Legs->bOwnerNoSee = false;
		Legs->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Legs->bCastDynamicShadow = true;
		Legs->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		// 'USkinnedMeshComponent::bChartDistanceFactor': bChartDistanceFactor is no longer useful, please remove references to it Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//Legs->bChartDistanceFactor = true;
		Legs->SetCollisionProfileName(CollisionProfileName);
		// UE 4.20 error C2248: 'UPrimitiveComponent::bGenerateOverlapEvents': cannot access private member declared in class 'UPrimitiveComponent'
		//Legs->bGenerateOverlapEvents = false;
		Legs->SetGenerateOverlapEvents(false);

		// Mesh acts as the head, as well as the parent for both animation and attachment.
		//Legs->AttachParent = Mesh;
		Legs->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		//Legs->SetMasterPoseComponent(Mesh);
		Legs->SetMasterPoseComponent(this->GetMesh());

		//Components.Add(Legs);
	}
}