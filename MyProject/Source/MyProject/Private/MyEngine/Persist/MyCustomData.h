#pragma once

#include "MyCustomData.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Global_Data_Access,_Data_Storage_Class_Accessible_From_Any_CPP_or_BP_Class_During_Runtime!
 */

USTRUCT(BlueprintType)
struct FMyCustomData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	FString Name = "Victory!";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	int32 Count = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	float Scale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joy Color")
	FLinearColor Color = FLinearColor::Red;

	FMyCustomData()
	{}
};

FORCEINLINE FArchive& operator<<(FArchive &Ar, FMyCustomData& TheStruct)
{
	Ar << TheStruct.Name;
	Ar << TheStruct.Count;
	Ar << TheStruct.Scale;
	Ar << TheStruct.Color;

	return Ar;
}