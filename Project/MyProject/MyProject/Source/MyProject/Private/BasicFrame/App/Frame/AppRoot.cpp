#include "MyProject.h"
#include "AppRoot.h"
#include "Ctx.h"

UAppRoot::UAppRoot(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void UAppRoot::BeginPlay()
{
	Super::BeginPlay();
}

void UAppRoot::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAppRoot::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (nullptr != GCtx)
	{
		GCtx->mainLoop();
	}
}