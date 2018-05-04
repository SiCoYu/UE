#include "MyProject.h"
#include "MyBluePrintToCppFunctionLibrary.h"
#include "MyBluePrintBase.h"
#include "Ctx.h"
#include "EngineApi.h"

UMyBluePrintToCppFunctionLibrary::UMyBluePrintToCppFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UMyBluePrintBase* UMyBluePrintToCppFunctionLibrary::getBPCtx()
{
	return GBPCtx.get();
}

ACharacter* UMyBluePrintToCppFunctionLibrary::getFirstCharacter()
{
	return EngineApi::getFirstCharacter();
}

AMyPlayerControllerBase* UMyBluePrintToCppFunctionLibrary::GetPlayerController()
{
	return EngineApi::GetPlayerController();
}