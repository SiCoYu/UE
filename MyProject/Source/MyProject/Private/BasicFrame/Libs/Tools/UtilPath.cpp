#include "MyProject.h"
#include "Containers/UnrealString.h"
#include "Misc/Paths.h"
#include "Core.h"
#include "CoreGlobals.h"
#include "HAL/FileManager.h"
#include "Common.h"
#include "UtilPath.h"

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

FString UtilPath::GetFilenameOnDisk(FString FullFilename)
{
	IFileManager& FileManager = IFileManager::Get();
	FString DiskFilename = FileManager.GetFilenameOnDisk(*FullFilename);
	return DiskFilename;
}

FString UtilPath::ConvertToSandboxPath(FString FullFilename)
{
	//const FString ThePath = FPaths::ConvertToSandboxPath(FPaths::GameLogDir());
	//IFileManager& FileManager = IFileManager::Get();
	FString DiskFilename = GSandboxPlatformFile->ConvertToSandboxPath(*FullFilename);
	return DiskFilename;
}

FString UtilPath::FPaths_ConvertToSandboxPath(FString FullFilename)
{
	return FPaths::ConvertToSandboxPath(FullFilename, TEXT("aaaa"));
}

void UtilPath::NormalizeDirectoryName(FString& InPath)
{
	FPaths::NormalizeDirectoryName(InPath);
}