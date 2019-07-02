#include "MyProject.h"
#include "MyAnimInstanceBase.h"
#include "MyCharacterBase.h"
#include "Animation/AnimNode_StateMachine.h"	  // FAnimNode_StateMachine

UMyAnimInstanceBase::UMyAnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

UMyAnimInstanceBase::UMyAnimInstanceBase()
{
	this->mOwnerActor = nullptr;
}

void UMyAnimInstanceBase::testA()
{

}

void UMyAnimInstanceBase::NativeInitializeAnimation()
{
	//Very Important Line
	Super::NativeInitializeAnimation();

	//Cache the owning pawn for use in Tick
	this->mOwnerActor = this->TryGetPawnOwner();
}

//Tick
void UMyAnimInstanceBase::NativeUpdateAnimation(float DeltaTimeX)
{
	//Very Important Line
	Super::NativeUpdateAnimation(DeltaTimeX);

	//Always Check Pointers
	if (!this->mOwnerActor)
	{
		return;
	}

	//Set whether moving or not
	this->IsMoving = (this->mOwnerActor->GetVelocity().SizeSquared() > 25);
}

bool UMyAnimInstanceBase::IsInMoving()
{
	ACharacter* character = Cast<ACharacter>(this->GetOwnerActor());
	if (!character)
		return false;

	float wallSpeed = FVector::DotProduct(character->GetVelocity(), character->GetActorRotation().Vector());
	return wallSpeed > 0.f ? true : false;
}

AActor* UMyAnimInstanceBase::GetOwnerActor()
{
	if (!this->mOwnerActor)
	{
		APawn* owner = this->TryGetPawnOwner();
		this->mOwnerActor = owner ? Cast<ACharacter>(owner) : nullptr;
	}

	return this->mOwnerActor;
}

void UMyAnimInstanceBase::AnimNotify_Begin(UAnimNotify * Notify)
{
	AMyCharacterBase* myChar = Cast<AMyCharacterBase>(this->GetOwnerActor());
	if (myChar)
	{
		FString str = FString::Printf(TEXT("--- AnimNotify_Begin - %d"), myChar->mHealth);
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	}
}

void UMyAnimInstanceBase::AnimNotify_End(UAnimNotify * Notify)
{
	FString str = FString::Printf(TEXT("--- AnimNotify_End"));
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str);
}

bool UMyAnimInstanceBase::HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
	return Super::HandleNotify(AnimNotifyEvent);
}

float UMyAnimInstanceBase::getCurUnitAnimTime(int32 AssetPlayerIndex)
{
	float ret = this->GetInstanceAssetPlayerTimeFraction(AssetPlayerIndex);
	return ret;
}

void UMyAnimInstanceBase::onMyTriggerSingleAnimNotify(FString NotifyName)
{

}

FName UMyAnimInstanceBase::getCurStateNameInStateMachine(FName MachineName)
{
	int32 MachineIndex = this->GetStateMachineIndex(MachineName);
	FAnimNode_StateMachine* StateMachine = this->GetStateMachineInstance(MachineIndex);
	return StateMachine->GetCurrentStateName();
}