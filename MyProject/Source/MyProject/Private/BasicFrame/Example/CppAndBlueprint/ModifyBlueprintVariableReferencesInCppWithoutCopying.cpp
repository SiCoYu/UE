//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#include "MyProject.h"
#include "ModifyBlueprintVariableReferencesInCppWithoutCopying.h"

//~~~

void UModifyBlueprintVariableReferencesInCppWithoutCopying::VictoryIntIncrement(UPARAM(ref) int32& Int, int32& IntOut)
{
	Int++;
	IntOut = Int;
}

//~~~

void UModifyBlueprintVariableReferencesInCppWithoutCopying::VictorySortIntArray(UPARAM(ref) TArray<int32>& IntArray, TArray<int32>& IntArrayRef)
{
	IntArray.Sort();
	IntArrayRef = IntArray;
}