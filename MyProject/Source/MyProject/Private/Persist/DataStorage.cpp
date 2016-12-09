#include "MyProject.h"
#include "DataStorage.h"

UDataStorage::UDataStorage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "E:/Solus";

	SolusEssentialVector = FVector(9000, 0, 0);
}