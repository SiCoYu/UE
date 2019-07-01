#include "MyProject.h"
#include "MyAnimController.h"
#include "MyAnimInstanceBase.h"
#include "GameFramework/Actor.h"

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

MY_END_NAMESPACE