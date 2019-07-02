#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "UObject/NoExportTypes.h"
#include "MyFbxMatInfo.h"

struct MYPROJECTEDITOR_API FMyFbxImportFilesInfo
{
	FString DirPath_MyFbxObject;
	FString DirName_MyFbxObject;

	TArray<FString> FilePaths_MyFbxModels;
	TSet<FString> FilePaths_MyFbxAnimations;

	FString FilePath_AnimationXml;
	FString FilePath_AnimationEventXml;
	FString FilePath_AnimationInfoXml;
	FString FilePath_AnimationSoundEventXml;
	FString FilePath_MyFbxXml;
	FString FilePath_SceneXml;

	TMap<FString, FMyFbxMatInfo> Map_MyFbxMatsInfo;

	FMyFbxImportFilesInfo(const FString& FilePath_MyFbxXml);
};