#include "MyProject.h"
#include "MyFunctionLibrary.h"
#include "MyBluePrintBase.h"
#include "Ctx.h"

UMyFunctionLibrary::UMyFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UMyDataStorage* UMyFunctionLibrary::GetSolusData(bool& IsValid)
{
	IsValid = false;
	UMyDataStorage* DataInstance = Cast<UMyDataStorage>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	IsValid = true;
	return DataInstance;
}