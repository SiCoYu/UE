#include "UtilPath.h"
#include "Containers/UnrealString.h"
#include "Misc/Paths.h"
#include "Core.h"
#include "CoreGlobals.h"

FString UtilPath::BaseDir()
{
	//InstallDir/WindowsNoEditor/GameName/Binaries/Win64
	const FString ThePath = FString(FPlatformProcess::BaseDir());
	return ThePath;
}

FString UtilPath::RootDir()
{
	//InstallDir/WindowsNoEditor/
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir());
	return ThePath;
}

FString UtilPath::GameDir()
{
	//InstallDir/WindowsNoEditor/GameName
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	return ThePath;
}

FString UtilPath::GameContentDir()
{
	//InstallDir/WindowsNoEditor/GameName/Content
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir());
	return ThePath;
}

FString UtilPath::GameSavedDir()
{
	//InstallDir/WindowsNoEditor/GameName/Saved
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir());
	return ThePath;
}

FString UtilPath::GameLogDir()
{
	//InstallDir/WindowsNoEditor/GameName/Saved/Logs
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameLogDir());
	return ThePath;
}