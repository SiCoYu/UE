#include "MyProject.h"
#include "MyProjectFunctionLibrary.h"

UMyProjectFunctionLibrary::UMyProjectFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

USolusDataSingleton* UMyProjectFunctionLibrary::GetSolusData(bool& IsValid)
{
	IsValid = false;
	UDataStorage* DataInstance = Cast<UDataStorage>(GEngine->GameSingleton);

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	IsValid = true;
	return DataInstance;
}
