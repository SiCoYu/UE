#pragma once

#include "UnrealString.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SortArrayBPFunctionLibrary.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Blueprint_Node:_Sort_Array_of_Actors_By_Field
 */

UENUM(BlueprintType)
enum class ESortDirection : uint8
{
	ASCENDING UMETA(DisplayName = "Ascending"),
	DESCENDING UMETA(DisplayName = "Descending")
};

UCLASS()
class USortArrayBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "Sort Array", CompactNodeTitle = "SORTARRAY", ArrayParm = "TargetArray|ArrayProperty"), Category = "Utilities|Array")
		static void Array_Sort(const TArray<int32>& TargetArray, const UArrayProperty* ArrayProperty, const FString &FieldName, ESortDirection SortDirection);
	static void GenericArray_Sort(void* TargetArray, const UArrayProperty* ArrayProp, const FString &FieldName, ESortDirection SortDirection);

	DECLARE_FUNCTION(execArray_Sort)
	{
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;

		P_GET_OBJECT(UArrayProperty, ArrayProperty);
		PARAM_PASSED_BY_REF(FieldName, UStrProperty, FString);
		PARAM_PASSED_BY_VAL(SortDirection, UByteProperty, ESortDirection);
		P_FINISH;

		GenericArray_Sort(ArrayAddr, ArrayProperty, FieldName, SortDirection);
	}
};

struct FXXXCustomThunkTemplates
{
	template<typename T>
	static void Array_Sort(TArray<T>& TargetArray, const UArrayProperty* ArrayProperty, const FString &FieldName, ESortDirection SortDirection)
	{
		UXXXBlueprintFunctionLibrary::GenericArray_Sort(&TargetArray, ArrayProperty, FieldName, SortDirection);
	}
};