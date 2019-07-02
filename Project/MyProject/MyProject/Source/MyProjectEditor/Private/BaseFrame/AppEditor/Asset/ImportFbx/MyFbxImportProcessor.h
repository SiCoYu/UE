// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "UObject/NoExportTypes.h"
#include "ImportResult.h"
#include "MyFbxMatInfo.h"
#include "MyFbxModelType.h"
#include "MyFbxImportProcessor.generated.h"

/**
 * @brief UMyFbxProcessor
 */
UCLASS()
class MYPROJECTEDITOR_API UMyFbxProcessor : public UObject
{
	GENERATED_BODY()
	
public:
	static const FString DirName_MyFbxAnimations;
	static const FString DirName_MyFbxModels;
	static const FString EditorDir_Textures;
	static const FString EditorDir_SimpleMaterials;

	static const FString EditorDir_HumanSkinMaterials;
	static const FString EditorDir_MaterialInstances;
	static const FString DirPath_AllModels;
	static const FString EditorDir_AllModels;
	static const FString FilePath_ErrorFile;

	TMap<FName, FAssetData> AssetDataMap_SimpleMaterials;
	TMap<FName, FAssetData> AssetDataMap_HumanSkinMaterials;
	TMap<FName, FAssetData> AssetDataMap_Textures;

	UPROPERTY()
	class UFbxFactory* SkeletalFbxFactory;
	UPROPERTY()
	class UFbxFactory* StaticFbxFactory;
	UPROPERTY()
	class UMaterialInstanceConstantFactoryNew* MIConstantFactoryNew;

public:
	UMyFbxProcessor(const FObjectInitializer& ObjectInitializer);
	void Initialize();
	void Uninitialize();

	class UStaticMesh* ImportStaticMesh(const FString& FilePath_MyFbxModel, const FString& EditorDir_ModelPackage, EImportResult& Result);
	class USkeletalMesh* ImportSkeletalMesh(const FString& FilePath_MyFbxModel, const FString& EditorDir_ModelPackage, EImportResult& Result);
	// class USkeletalMesh* ImportSkeletalMesh();
	static FString GetTextureNameFromXmlNode(class FXmlNode* XmlNode);
	static FString GetEditorMatName(FMyFbxMatInfo MatInfo);
	static EMyFbxModelType GetMyFbxModelType(const FString& FilePath_MyFbxXml);

	static void AddError(const FString& ErrorMessage);
	static bool AreMaterialInstanceParametersSame(class UMaterialInstanceConstant* MIConstant, FMyFbxMatInfo MatInfo);

	static void ParseMyFbxXmlForMaterials(const FString& FilePath_MyFbxXml, TMap<FString, FMyFbxMatInfo>& OutMap_MyFbxMatsInfo);
	bool FillMaterialInstanceTextureParameter(class UMaterialInstanceConstant* MIConstant, FName ParamName, FName TextureName);
	bool FillMaterialInstanceParameters(class UMaterialInstanceConstant* MIConstant, const FString& EditorMatName, const FMyFbxMatInfo& MatInfo);
	EImportResult CreateAndApplyStaticMeshMaterials(class UStaticMesh* StaticMesh, TMap<FString, FMyFbxMatInfo> Map_MyFbxMatsInfo);
	EImportResult CreateAndApplySkeletalMeshMaterials(class USkeletalMesh* SkeletalMesh, TMap<FString, FMyFbxMatInfo> Map_MyFbxMatsInfo);
	EImportResult ImportMyFbxModels(const TArray<FString>& InPaths_MyFbxXmlFilesToLoad, TArray<FString>& OutPaths_MyFbxXmlFilesLoaded);
};
