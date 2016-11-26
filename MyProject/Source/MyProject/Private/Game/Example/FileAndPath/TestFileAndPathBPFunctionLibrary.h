#pragma once

#include "UnrealString.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestFileAndPathBPFunctionLibrary.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Algorithm_Analysis:_Create_Directory_Recursively
 */

class UTestFileAndPathBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	// If you try to create the above directory, YourSubLevels, supplying the entire path, the CreateDirectory function will fail if all of the super directories do not exist. 
	UFUNCTION(BlueprintCallable, Category = "TestFileAndPath")
	static void CreateDirectory(FString path);

	UFUNCTION(BlueprintCallable, Category = "TestFileAndPath")
	static void CreateDirectoryRecursively(FString path);

	UFUNCTION(BlueprintCallable, Category = "TestFileAndPath")
	static FORCEINLINE void NormalizeDirectoryName(FString path)
	{
		// Normalize all / and \ to TEXT("/") and remove any trailing TEXT("/") if the character before that is not a TEXT("/") or a colon
		FPaths::NormalizeDirectoryName(path);
	}

	UFUNCTION(BlueprintCallable, Category = "TestFileAndPath")
	static FORCEINLINE void TestUse()
	{
		FString NewFolder =
			"C:/Users/Rama/Documents/Victory/FolderSong/FolderDance/FolderRain/FolderRainbow/";

		//remove UMyFunctionLibrary:: if you removed the "static"
		CreateDirectoryRecursively(NewFolder);
	}

	UFUNCTION(BlueprintCallable, Category = "TestFileAndPath")
	static FORCEINLINE void NormalizeDirectoryNameTwo(FString path)
	{
		// Normalize all / and \ to TEXT("/") and remove any trailing TEXT("/") if the character before that is not a TEXT("/") or a colon
		FPaths::NormalizeDirectoryName(path);

		//Normalize removes the last "/", but my algorithm wants it
		path += "/";
	}
};