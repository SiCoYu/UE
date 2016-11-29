#pragma once

#include "UnrealString.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShareBPFunctionLibrary.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Blueprint_Function_Library,_Create_Your_Own_to_Share_With_Others
 */

UCLASS()
class UShareBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "VictoryBPLibrary")
	static FString GetHappyMessage();

	/** Saves text to filename of your choosing, make sure include whichever file extension you want in the filename, ex: SelfNotes.txt . Make sure to include the entire file path in the save directory, ex: C:\MyGameDir\BPSavedTextFiles */
	UFUNCTION(BlueprintCallable, Category = "VictoryBPLibrary")
	static bool SaveStringTextToFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting = false);
};