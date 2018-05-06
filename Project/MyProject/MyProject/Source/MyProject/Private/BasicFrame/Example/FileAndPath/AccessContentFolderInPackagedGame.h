#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/Platform.h"
#include "Containers/UnrealString.h"
#include "Misc/Paths.h"
#include "AccessContentFolderInPackagedGame.generated.h"

/**
* @brief https://wiki.unrealengine.com/How_To_Package_Extra_NonUASSET_Files_With_Your_Game
*/

UCLASS()
class UAccessContentFolderInPackagedGame : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static FORCEINLINE void GetContentPath()
	{
		// UE 4.19.1 warning C4996: 'FPaths::GameContentDir': FPaths::GameContentDir() has been superseded by FPaths::ProjectContentDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//InstallDir/WindowsNoEditor/GameName/Content
		//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir());
		const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	}
};