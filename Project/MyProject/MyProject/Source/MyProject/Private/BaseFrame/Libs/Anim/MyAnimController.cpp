#include "MyProject.h"
#include "MyAnimController.h"
#include "MyAnimInstanceBase.h"
#include "GameFramework/Actor.h"
#include "MyCharacterBase.h"

MY_BEGIN_NAMESPACE(MyNS)

void MyAnimController::init()
{

}

void MyAnimController::dispose()
{

}

void MyAnimController::setActor(AActor* actor)
{
	this->mActorPtr = actor;
	this->mMeshComp = this->mActorPtr->FindComponentByClass<USkeletalMeshComponent>();
	this->mAnimInstancePtr = Cast<UMyAnimInstanceBase>(this->mMeshComp->GetAnimInstance());
	this->mSkeletalMesh = this->mMeshComp->SkeletalMesh;
	this->mSkeleton = this->mSkeletalMesh->Skeleton;
	//this->mMesh = this->mSkeletalMesh->BodySetup;
}

void MyAnimController::setAnimBlueprint_Test()
{
	AMyCharacterBase* NewSMActor = nullptr;
	//// Term Component
	//NewSMActor->GetSkeletalMeshComponent()->UnregisterComponent();

	//// Change properties
	//NewSMActor->GetSkeletalMeshComponent()->SkeletalMesh = SkeletalMesh;
	//if (NewSMActor->GetWorld()->IsGameWorld())
	//{
	//	NewSMActor->ReplicatedMesh = SkeletalMesh;
	//}

	//// Init Component
	//NewSMActor->GetSkeletalMeshComponent()->RegisterComponent();
	//if (AnimBlueprint)
	//{
	//	NewSMActor->GetSkeletalMeshComponent()->SetAnimInstanceClass(AnimBlueprint->GeneratedClass);
	//}
}

MY_END_NAMESPACE