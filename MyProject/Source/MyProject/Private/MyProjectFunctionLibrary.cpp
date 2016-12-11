#include "MyProject.h"
#include "MyProjectFunctionLibrary.h"

UMyProjectFunctionLibrary::UMyProjectFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UMyDataStorage* UMyProjectFunctionLibrary::GetSolusData(bool& IsValid)
{
	IsValid = false;
	UMyDataStorage* DataInstance = Cast<UMyDataStorage>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	IsValid = true;
	return DataInstance;
}
