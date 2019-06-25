#include "MyProject.h"
#include "MyAnimInstanceBase.h"

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
	mOwnerActor = TryGetPawnOwner();
}

//Tick
void UMyAnimInstanceBase::NativeUpdateAnimation(float DeltaTimeX)
{
	//Very Important Line
	Super::NativeUpdateAnimation(DeltaTimeX);

	//Always Check Pointers
	if (!mOwnerActor)
	{
		return;
	}

	//Set whether moving or not
	IsMoving = (mOwnerActor->GetVelocity().SizeSquared() > 25);
}

bool UMyAnimInstanceBase::IsInMoving()
{
	//ACharacter* character = GetOwnerActor();
	//if (!character)
	//	return false;

	//float wallSpeed = FVector::DotProduct(character->GetVelocity(), character->GetActorRotation().Vector());
	//return wallSpeed > 0.f ? true : false;
	return false;
}

AActor* UMyAnimInstanceBase::GetOwnerActor()
{
	if (!mOwnerActor)
	{
		APawn* owner = TryGetPawnOwner();
		mOwnerActor = owner ? Cast<ACharacter>(owner) : nullptr;
	}
	return mOwnerActor;
}

void UMyAnimInstanceBase::AnimNotify_Begin(UAnimNotify * Notify)
{
	//AMyChar* mychar = Cast<AMyChar>(GetOwnerChar());
	//if (mychar)
	//{
	//	FString str = FString::Printf(TEXT("--- AnimNotify_Begin - %d"), mychar->mHealth);
	//	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	//}
}

void UMyAnimInstanceBase::AnimNotify_End(UAnimNotify * Notify)
{
	//FString str = FString::Printf(TEXT("--- AnimNotify_End"));
	//GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str);
}

bool UMyAnimInstanceBase::HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
	Super::HandleNotify(AnimNotifyEvent);


}