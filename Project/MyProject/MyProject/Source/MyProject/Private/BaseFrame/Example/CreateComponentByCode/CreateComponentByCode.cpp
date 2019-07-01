#include "MyProject.h"
#include "PlayAnimByCppActor.h"
#include "Components/SkeletalMeshComponent.h"	// USkeletalMeshComponent
#include "Animation/AnimSingleNodeInstance.h"

APlayAnimByCppActor::APlayAnimByCppActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void APlayAnimByCppActor::TestReplaceSkeletonMesh()
{
	USkeletalMesh* MyMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/MyMesh.MyMesh'"));
	APlayAnimByCppActor* Actor = GetWorld()->SpawnActor<APlayAnimByCppActor>(FVector(1000, 1000, 0), FRotator(0, 0, 0));
	Actor->FindComponentByClass<USkeletalMeshComponent>()->SetSkeletalMesh(MyMesh);
}

void APlayAnimByCppActor::PlayBlendSpaceAnim()
{
	ASkeletalMeshActor* Skel = Cast<ASkeletalMeshActor>(this);
	if (Skel)
	{
		USkeletalMeshComponent* Mesh = Skel->GetSkeletalMeshComponent();
		if (Mesh)
		{
			Mesh->PlayAnimation(BlendSpace, true);
			FVector BlendParams(50.0f, 0.0f, 0.0f);
			Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
		}
	}
}

void APlayAnimByCppActor::PlayAnimSequence()
{
	USkeletalMeshComponent* Mesh = this->FindComponentByClass<USkeletalMeshComponent>();
	if (Mesh)
	{
		UAnimInstance* AnimInst = Mesh->GetAnimInstance();
		if (AnimInst)
		{
			AnimInst->PlaySlotAnimationAsDynamicMontage(MyAnimSequence, TEXT("UpperBody"), 0.1f, 0.1f, 1.0f, 30.0f);
		}
	}
}

void APlayAnimByCppActor::PlayMontage()
{
	USkeletalMeshComponent* Mesh = this->FindComponentByClass<USkeletalMeshComponent>();
	if (Mesh)
	{
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		if (AnimInstance)
		{
			MyAnimTimer = AnimInstance->Montage_Play(MyMontage);
			GetWorldTimerManager().SetTimer(this->PauseMontageTimerHandle, this, &APlayAnimByCppActor::PauseMontageFunc, MyAnimTimer, false);
		}
	}
}

void APlayAnimByCppActor::PauseMontageFunc()
{

}

void APlayAnimByCppActor::SetAnimInstanceClass(UClass* NewClass)
{
	USkeletalMeshComponent* Mesh = this->FindComponentByClass<USkeletalMeshComponent>();
	if (Mesh)
	{
		UAnimBlueprintGeneratedClass* MeshAnim = LoadObject<UAnimBlueprintGeneratedClass>(NULL, TEXT("/Game/Character/HeroTPP_AnimBlueprint.HeroTPP_AnimBlueprint"));
		Mesh->SetAnimInstanceClass(MeshAnim);
		// UE_DEPRECATED(4.11, "This property is deprecated. Please use AnimClass instead")
		//Mesh->AnimBlueprintGeneratedClass = MeshAnim;
		//Mesh->AnimClass = MeshAnim;
	}
}