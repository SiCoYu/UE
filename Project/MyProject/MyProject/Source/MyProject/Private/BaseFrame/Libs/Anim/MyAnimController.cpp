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
	USkeletalMeshComponent* Mesh = this->mActorPtr->FindComponentByClass<USkeletalMeshComponent>();
	this->mAnimInstancePtr = Cast<UMyAnimInstanceBase>(Mesh->GetAnimInstance());
}

MY_END_NAMESPACE