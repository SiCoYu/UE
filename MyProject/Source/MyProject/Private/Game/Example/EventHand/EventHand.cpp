#include "MyProject.h"
#include "EventHand.h"
#include "Delegates/Delegate.h"

AEventHand::AEventHand(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AEventHand::OnOverlap(AActor* OtherActor)
{
	
}

void AEventHand::addEventHandle()
{
	//this->OnActorBeginOverlap.AddDynamic(this, &AEventHand::OnOverlap);
	AddDynamic(this, &AEventHand::OnOverlap);
}