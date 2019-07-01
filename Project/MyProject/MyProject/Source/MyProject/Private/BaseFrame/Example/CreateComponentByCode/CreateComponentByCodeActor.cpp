#include "MyProject.h"
#include "CreateComponentByCodeActor.h"
#include "Components/SkeletalMeshComponent.h"	// USkeletalMeshComponent
#include "Animation/AnimSingleNodeInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"		// UBehaviorTreeComponent

ACreateComponentByCodeActor::ACreateComponentByCodeActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void ACreateComponentByCodeActor::createSkeletalMeshComponent()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> npcSkeletalMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> npcAmin(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
	UAnimBlueprintGeneratedClass* AminClass = LoadObject<UAnimBlueprintGeneratedClass>(UAnimBlueprintGeneratedClass::StaticClass(), TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
	this->mMeshCompPtr = this->CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NpcMesh"));
	this->mMeshCompPtr->SetSkeletalMesh(npcSkeletalMesh.Object);
	this->mMeshCompPtr->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	UClass* ap = (UClass*)npcAmin.Object->GeneratedClass;
	this->mMeshCompPtr->SetAnimInstanceClass(ap);
	this->mMeshCompPtr->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	//	this->RootComponent = this->mMeshCompPtr;
	this->mMeshCompPtr->AttachTo(this->RootComponent);
}

void ACreateComponentByCodeActor::createBehaviorTreeComponent()
{
	this->mBehaviorTreeCompPtr = this->CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("NpcBehaviorTree"));
	this->mBehaviorTreeCompPtr->
}