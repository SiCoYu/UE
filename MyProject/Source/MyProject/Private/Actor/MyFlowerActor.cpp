#include "MyProject.h"
#include "MyFlowerActor.h"

AMyFlowerActor::AMyFlowerActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AMyFlowerActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}