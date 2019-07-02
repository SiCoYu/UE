#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "UObject/NoExportTypes.h"
#include "MyFbxMatInfo.h"

struct MYPROJECTEDITOR_API FMyFbxImportFilesInfo
{
	FString DirPath_EluObject;
	FString DirName_EluObject;

	TArray<FString> FilePaths_EluModels;
	TSet<FString> FilePaths_EluAnimations;

	FString FilePath_AnimationXml;
	FString FilePath_AnimationEventXml;
	FString FilePath_AnimationInfoXml;
	FString FilePath_AnimationSoundEventXml;
	FString FilePath_EluXml;
	FString FilePath_SceneXml;

	TMap<FString, FMyFbxMatInfo> Map_EluMatsInfo;

	FMyFbxImportFilesInfo(const FString& FilePath_EluXml);
};