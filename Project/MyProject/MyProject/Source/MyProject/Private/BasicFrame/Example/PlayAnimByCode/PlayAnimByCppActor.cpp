#include "MyProject.h"
#include "PlayAnimByCppActor.h"

APlayAnimByCppActor::APlayAnimByCppActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void APlayAnimByCppActor::TestReplaceSkeletonMesh()
{
	USkeletalMesh* MyMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/MyMesh.MyMesh'"));
	APlayAnimByCppActor* Actor = World->SpawnActor<APlayAnimByCppActor>(FVector(1000, 1000, 0), FRotator(0, 0, 0));
	Actor->GetMesh()->SetSkeletalMesh(MyMesh);
}

void APlayAnimByCppActor::PlayBlendSpaceAnim()
{
	ASkeletalMeshActor* Skel = Cast<ASkeletalMeshActor>(MyActor);
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
	USkeletalMeshComponent* Mesh = MyActor->FindComponentByClass<USkeletalMeshComponent>();
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
	MyAnimTimer = AnimInstance->Montage_Play(MyMontage);
	GetWorldTimerManager().SetTimer(PauseMontageTimerHandle, this, &MyActor::PauseMontageFunc, MyAnimTimer, false);
}

void APlayAnimByCppActor::SetAnimInstanceClass(UClass* NewClass)
{
	UAnimBlueprintGeneratedClass* MeshAnim = LoadObject<UAnimBlueprintGeneratedClass>(NULL, TEXT("/Game/Character/HeroTPP_AnimBlueprint.HeroTPP_AnimBlueprint"));
	Mesh->SetAnimInstanceClass(MeshAnim);
}