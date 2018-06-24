#include "MyProject.h"
#include "AppRoot.h"
#include "Ctx.h"

UAppRoot::UAppRoot(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void UAppRoot::BeginPlay()
{

}

void UAppRoot::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

void UAppRoot::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (nullptr != GCtx)
	{
		GCtx->mainLoop();
	}
}