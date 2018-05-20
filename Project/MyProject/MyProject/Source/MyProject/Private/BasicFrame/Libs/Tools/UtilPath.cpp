#include "MyProject.h"
#include "Containers/UnrealString.h"
#include "Misc/Paths.h"
#include "Core.h"
#include "CoreGlobals.h"
#include "HAL/FileManager.h"
#include "Prequisites.h"
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
	// UE 4.19.1 warning C4996: 'FPaths::GameDir': FPaths::GameDir() has been superseded by FPaths::ProjectDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	return ThePath;
}

FString UtilPath::GameContentDir()
{
	// UE 4.19.1 warning C4996: 'FPaths::GameContentDir': FPaths::GameContentDir() has been superseded by FPaths::ProjectContentDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName/Content
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir());
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	return ThePath;
}

FString UtilPath::GameSavedDir()
{
	// UE 4.19.1 warning C4996: 'FPaths::GameSavedDir': FPaths::GameSavedDir() has been superseded by FPaths::ProjectSavedDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName/Saved
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir());
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	return ThePath;
}

FString UtilPath::GameLogDir()
{
	// UE 4.19.1 warning C4996: 'FPaths::GameLogDir': FPaths::GameLogDir() has been superseded by FPaths::ProjectLogDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName/Saved/Logs
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameLogDir());
	const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectLogDir());
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
	FString DiskFilename = GFileSysSandboxPlatformFile->ConvertToSandboxPath(*FullFilename);
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

bool UtilPath::FileExists(const std::string& InPath)
{
	FString convPath = UtilStr::ConvStdStr2FString(const_cast<std::string&>(InPath));
	return FPaths::FileExists(convPath);
}