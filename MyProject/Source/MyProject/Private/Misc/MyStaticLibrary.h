#pragma once

#include "MyStaticLibrary.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Static_Function_Libraries,_Your_Own_Version_of_UE4_C%2B%2B,_No_Engine_Compile_Times
 */

UCLASS()
class UMyStaticLibrary : public UObject
{
	GENERATED_UCLASS_BODY()

	//FORCEINLNE function
	static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor) return false;
		if (!TheActor->IsValidLowLevel()) return false;
		return true;
	}

	//cpp function
	static int32 ComplicatedGameDataAnalysis();
};