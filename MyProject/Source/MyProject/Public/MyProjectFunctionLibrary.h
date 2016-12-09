#pragma once

#include "MyProject.h"
#include "DataStorage.h"
#include "MyProjectFunctionLibrary.generated.h"

UCLASS()
class UMyProjectFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UMyProjectFunctionLibrary(const FObjectInitializer& ObjectInitializer);

	// https://wiki.unrealengine.com/Global_Data_Access,_Data_Storage_Class_Accessible_From_Any_CPP_or_BP_Class_During_Runtime!
	UFUNCTION(BlueprintPure, Category = "Solus Data Singleton")
	static UDataStorage* GetSolusData(bool& IsValid);
};