#include "MyProject.h"
#include "MyDataStorage.h"

UMyDataStorage::UMyDataStorage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "E:/Solus";

	SolusEssentialVector = FVector(9000, 0, 0);
}