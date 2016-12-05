//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Containers/Array.h"
#include "UObject/ObjectMacros.h"
#include "ModifyBlueprintVariableReferencesInCppWithoutCopying.generated.h"

/**
* @brief https://wiki.unrealengine.com/How_To_Modify_Blueprint_Variable_References_In_C%2B%2B_Without_Copying
*/

UCLASS()
class UModifyBlueprintVariableReferencesInCppWithoutCopying : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** Easily increment an integer! */
	UFUNCTION(BlueprintCallable, meta = (CompactNodeTitle = "++", Keywords = "increment integer"), Category = "VictoryBPLibrary|Math|Integer")
	static void VictoryIntIncrement(UPARAM(ref) int32& Int, int32& IntOut);

	/** Sort an integer array, smallest value will be at index 0 after sorting. Modifies the input array, no new data created. <3 Rama */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "sort integer array"), Category = "VictoryBPLibrary|Array")
	static void VictorySortIntArray(UPARAM(ref) TArray<int32>& IntArray, TArray<int32>& IntArrayRef);
};