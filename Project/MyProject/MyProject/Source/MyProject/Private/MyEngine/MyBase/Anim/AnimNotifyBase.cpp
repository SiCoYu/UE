#include "MyProject.h"
#include "AnimNotifyBase.h"
#include "MyAnimInstanceBase.h"

UAnimNotifyBase::UAnimNotifyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UAnimNotifyBase::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UMyAnimInstanceBase* animInstance = Cast<UMyAnimInstanceBase>(MeshComp->GetAnimInstance());
	//AActor* actor = Cast<AActor>(MeshComp->GetOuter());
	//animInstance = actor->FindComponentByClass<UMyAnimInstanceBase>();

	if (nullptr != animInstance)
	{
		animInstance->onMyTriggerSingleAnimNotify(this->GetNotifyName());
	}
}