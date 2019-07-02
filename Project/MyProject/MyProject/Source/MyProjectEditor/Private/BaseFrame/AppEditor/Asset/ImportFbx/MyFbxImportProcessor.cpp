#include "MyFbxImportProcessor.h"
#include "XmlFile.h"
#include "Misc/Paths.h"
#include "ObjectTools.h"
#include "PackageTools.h"
#include "MessageDialog.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Editor/EditorEngine.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManagerGeneric.h"
#include "Factories/FbxAnimSequenceImportData.h"
#include "Materials/MaterialInstanceConstant.h"

#include "Kismet/KismetStringLibrary.h"
#include "Factories/FbxFactory.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "MyFbxImportFilesInfo.h"


const FString UMyFbxProcessor::DirName_MyFbxAnimations = FString("elu_animations");
const FString UMyFbxProcessor::DirName_MyFbxModels = FString("elu_model");

const FString UMyFbxProcessor::DirPath_AllModels = FString("F:/Game Dev/asset_dest/Model");
const FString UMyFbxProcessor::FilePath_ErrorFile = FString("F:/Game Dev/Unreal Projects/RaiderZAssets/data_files/errors.txt");

//~ Editor directories
const FString UMyFbxProcessor::EditorDir_Textures = FString("/Game/EOD/Texture");
const FString UMyFbxProcessor::EditorDir_SimpleMaterials = FString("/Game/EOD/Mats/RaiderZ_SimpleMats");
const FString UMyFbxProcessor::EditorDir_HumanSkinMaterials = FString("/Game/EOD/Mats/RaiderZ_HumanSkinMats");
const FString UMyFbxProcessor::EditorDir_MaterialInstances = FString("/Game/EOD/MIs");
const FString UMyFbxProcessor::EditorDir_AllModels = FString("/Game/EOD/Model");


UMyFbxProcessor::UMyFbxProcessor(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{	
	SkeletalFbxFactory = nullptr;
	StaticFbxFactory = nullptr;
	MIConstantFactoryNew = nullptr;
}

void UMyFbxProcessor::Initialize()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> AssetData_Temp;
	bool bFoundAssets;
	FName EditorPathToAssets;

	AssetDataMap_Textures.Empty();
	AssetDataMap_SimpleMaterials.Empty();
	AssetDataMap_HumanSkinMaterials.Empty();

	EditorPathToAssets = FName(*PackageTools::SanitizePackageName(UMyFbxProcessor::EditorDir_SimpleMaterials));
	bFoundAssets = AssetRegistryModule.Get().GetAssetsByPath(EditorPathToAssets, AssetData_Temp, true);
	if (bFoundAssets)
	{
		for (FAssetData AssetData : AssetData_Temp)
		{
			AssetDataMap_SimpleMaterials.Add(AssetData.AssetName, AssetData);
		}
	}
	AssetData_Temp.Empty();

	EditorPathToAssets = FName(*PackageTools::SanitizePackageName(UMyFbxProcessor::EditorDir_HumanSkinMaterials));
	bFoundAssets = AssetRegistryModule.Get().GetAssetsByPath(EditorPathToAssets, AssetData_Temp, true);
	if (bFoundAssets)
	{
		for (FAssetData AssetData : AssetData_Temp)
		{
			AssetDataMap_HumanSkinMaterials.Add(AssetData.AssetName, AssetData);
		}
	}
	AssetData_Temp.Empty();

	EditorPathToAssets = FName(*PackageTools::SanitizePackageName(UMyFbxProcessor::EditorDir_Textures));
	bFoundAssets = AssetRegistryModule.Get().GetAssetsByPath(EditorPathToAssets, AssetData_Temp, true);
	if (bFoundAssets)
	{
		for (FAssetData AssetData : AssetData_Temp)
		{
			AssetDataMap_Textures.Add(AssetData.AssetName, AssetData);
		}
	}
	AssetData_Temp.Empty();

	//~ begin new code
	if (SkeletalFbxFactory)
	{
		SkeletalFbxFactory->CleanUp();
		SkeletalFbxFactory->ConditionalBeginDestroy();
	}
	SkeletalFbxFactory = NewObject<UFbxFactory>();
	SkeletalFbxFactory->EnableShowOption();

	if (StaticFbxFactory)
	{
		StaticFbxFactory->CleanUp();
		StaticFbxFactory->ConditionalBeginDestroy();
	}
	StaticFbxFactory = NewObject<UFbxFactory>();
	StaticFbxFactory->EnableShowOption();

	if (!MIConstantFactoryNew)
	{
		MIConstantFactoryNew = NewObject<UMaterialInstanceConstantFactoryNew>();
	}
	// MIConstantFactoryNew->AddToRoot();
	//~ end new code

	/*
	if (!SkeletalFbxFactory)
	{
		SkeletalFbxFactory = NewObject<UFbxFactory>();
	}
	SkeletalFbxFactory->EnableShowOption();
	// SkeletalFbxFactory->AddToRoot();

	if (!StaticFbxFactory)
	{
		StaticFbxFactory = NewObject<UFbxFactory>();
	}
	StaticFbxFactory->EnableShowOption();
	// StaticFbxFactory->AddToRoot();

	*/
}

void UMyFbxProcessor::Uninitialize()
{
	AssetDataMap_Textures.Empty();
	AssetDataMap_SimpleMaterials.Empty();
	AssetDataMap_HumanSkinMaterials.Empty();

	if (SkeletalFbxFactory)
	{
		SkeletalFbxFactory->CleanUp();
		SkeletalFbxFactory->ConditionalBeginDestroy();
	}

	if (StaticFbxFactory)
	{
		StaticFbxFactory->CleanUp();
		StaticFbxFactory->ConditionalBeginDestroy();
	}

	if (MIConstantFactoryNew)
	{
		MIConstantFactoryNew->CleanUp();
		MIConstantFactoryNew->ConditionalBeginDestroy();
	}
}

UStaticMesh * UMyFbxProcessor::ImportStaticMesh(const FString& FilePath_MyFbxModel, const FString& EditorDir_ModelPackage, EImportResult& Result)
{
	FString LogMessage;
	UStaticMesh* StaticMesh = nullptr;
	Result = EImportResult::Success;

	FString FileName_MyFbxModel = FPaths::GetBaseFilename(FilePath_MyFbxModel);
	FString StaticMeshName = FileName_MyFbxModel.Replace(TEXT("LOD"), TEXT(""));
	FString ModelPackageName = EditorDir_ModelPackage + FString("/") + StaticMeshName;
	ModelPackageName = PackageTools::SanitizePackageName(ModelPackageName);

	UPackage* ModelPackage = nullptr;
	if (FPackageName::DoesPackageExist(ModelPackageName))
	{
		ModelPackage = LoadPackage(nullptr, *ModelPackageName, LOAD_None);
		if (ModelPackage)
		{
			ModelPackage->FullyLoad();
		}

		LogMessage = ModelPackageName + FString(" already exists!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
	}
	else
	{
		ModelPackage = CreatePackage(nullptr, *ModelPackageName);
		ModelPackage->FullyLoad();
	}

	bool bImportCancelled = false;
	UObject* ImportedModel = StaticFbxFactory->ImportObject(UStaticMesh::StaticClass(),
															ModelPackage, FName(*StaticMeshName),
															EObjectFlags::RF_Standalone | EObjectFlags::RF_Public,
															FilePath_MyFbxModel,
															nullptr,
															bImportCancelled);

	// If user cancelled import, stop further processing
	if (bImportCancelled)
	{
		if (ModelPackage)
		{
			// @todo remove/delete package
			ModelPackage->ConditionalBeginDestroy();
		}

		LogMessage = FString("Import cancelled by user for static model: ") + FileName_MyFbxModel;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		Result = EImportResult::Cancelled;
		return StaticMesh;
	}

	if (!ImportedModel)
	{
		if (ModelPackage)
		{
			// @todo remove/delete package
			ModelPackage->ConditionalBeginDestroy();
		}

		// No need to stop execution because we will encounter this situation quite often, 
		// simply because some of the fbx files contain an empty scene.
		LogMessage = FString("Unable to import static model: ") + FileName_MyFbxModel;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		Result = EImportResult::Failure;
		return StaticMesh;
	}

	StaticMesh = Cast<UStaticMesh>(ImportedModel);

	if (!StaticMesh)
	{
		LogMessage = FString("Unabled to cast imported mesh to static mesh. Imported model name: ") + FilePath_MyFbxModel;
		UMyFbxProcessor::AddError(LogMessage);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		Result = EImportResult::Failure;
	}

	return StaticMesh;
}

USkeletalMesh * UMyFbxProcessor::ImportSkeletalMesh(const FString & FilePath_MyFbxModel, const FString & EditorDir_ModelPackage, EImportResult& Result)
{
	FString LogMessage;
	USkeletalMesh* SkeletalMesh = nullptr;
	Result = EImportResult::Success;

	FString FileName_MyFbxModel = FPaths::GetBaseFilename(FilePath_MyFbxModel);
	FString SkeletalMeshName = FileName_MyFbxModel.Replace(TEXT("LOD"), TEXT(""));
	FString ModelPackageName = EditorDir_ModelPackage + FString("/") + SkeletalMeshName;
	ModelPackageName = PackageTools::SanitizePackageName(ModelPackageName);

	UPackage* ModelPackage = nullptr;
	if (FPackageName::DoesPackageExist(ModelPackageName))
	{
		ModelPackage = LoadPackage(nullptr, *ModelPackageName, LOAD_None);
		if (ModelPackage)
		{
			ModelPackage->FullyLoad();
		}

		LogMessage = ModelPackageName + FString(" already exists!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
	}
	else
	{
		ModelPackage = CreatePackage(nullptr, *ModelPackageName);
		ModelPackage->FullyLoad();
	}

	bool bImportCancelled = false;
	UObject* ImportedModel = SkeletalFbxFactory->ImportObject(UStaticMesh::StaticClass(),
															  ModelPackage, FName(*SkeletalMeshName),
															  EObjectFlags::RF_Standalone | EObjectFlags::RF_Public,
															  FilePath_MyFbxModel,
															  nullptr,
															  bImportCancelled);

	// If user cancelled import, stop further processing
	if (bImportCancelled)
	{
		if (ModelPackage)
		{
			// @todo remove/delete package
			ModelPackage->ConditionalBeginDestroy();
		}

		LogMessage = FString("Import cancelled by user for skeletal model: ") + FileName_MyFbxModel;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		Result = EImportResult::Cancelled;
		return SkeletalMesh;
	}

	if (!ImportedModel)
	{
		if (ModelPackage)
		{
			// @todo remove/delete package
			ModelPackage->ConditionalBeginDestroy();
		}

		// No need to stop execution because we will encounter this situation quite often, 
		// simply because some of the fbx files contain an empty scene.
		LogMessage = FString("Unable to import skeletal model : ") + FileName_MyFbxModel;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		Result = EImportResult::Failure;
		return SkeletalMesh;
	}

	SkeletalMesh = Cast<USkeletalMesh>(ImportedModel);

	if (!SkeletalMesh)
	{
		LogMessage = FString("Unabled to cast imported mesh to skeletal mesh. Imported model name: ") + FilePath_MyFbxModel;
		UMyFbxProcessor::AddError(LogMessage);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		Result = EImportResult::Failure;
	}

	return SkeletalMesh;
}

FString UMyFbxProcessor::GetTextureNameFromXmlNode(FXmlNode* XmlNode)
{
	FString TextureName;

	if (XmlNode)
	{
		FString ChildContent = XmlNode->GetContent();
		TArray<FString> ChildContentSplitArray;
		ChildContent.ParseIntoArray(ChildContentSplitArray, *FString("."));
		if (ChildContentSplitArray.Num() > 0)
		{
			TextureName = FString("T_") + ObjectTools::SanitizeObjectName(ChildContentSplitArray[0]);
		}
	}

	return TextureName;
}

FString UMyFbxProcessor::GetEditorMatName(FMyFbxMatInfo MatInfo)
{
	if (MatInfo.bMaterialType_HumanFace)
	{
		return FString("Face_mat");
	}
	else if (MatInfo.bMaterialType_HumanBody)
	{
		return FString("Body_mat");
	}

	FString EditorMatName = FString("");

	if (!MatInfo.Texture_DiffuseMap.IsEmpty())
	{
		EditorMatName += FString("D");
	}
	if (!MatInfo.Texture_SpecularMap.IsEmpty())
	{
		EditorMatName += FString("S");
	}
	if (!MatInfo.Texture_NormalMap.IsEmpty())
	{
		EditorMatName += FString("N");
	}
	if (!MatInfo.Texture_SelfIlluminationMap.IsEmpty())
	{
		EditorMatName += FString("G");
	}
	EditorMatName += "_";

	if (!MatInfo.Texture_OpacityMap.IsEmpty())
	{
		if (MatInfo.bOpacityBlendModel_Translucent)
		{
			EditorMatName += FString("L");
		}
		else
		{
			EditorMatName += FString("T");
		}

		if (MatInfo.bOpacityMaskChannel_Alpha)
		{
			EditorMatName += FString("A");
		}
	}
	if (!MatInfo.Texture_ReflectMap.IsEmpty())
	{
		EditorMatName += FString("RA");
	}

	if (!EditorMatName.EndsWith(FString("_")))
	{
		EditorMatName += "_";
	}

	if (MatInfo.bAnimatedTexture_AllTextures)
	{
		EditorMatName += FString("ZP");
	}
	if(MatInfo.bAnimatedTexture_Diffuse)
	{
		EditorMatName += FString("DP");
	}
	if (MatInfo.bAnimatedTexture_Glow)
	{
		EditorMatName += FString("GP");
	}
	if (MatInfo.bAnimatedTexture_Normal)
	{
		EditorMatName += FString("NP");
	}
	if (MatInfo.bAnimatedTexture_Opacity)
	{
		EditorMatName += FString("TP");
	}
	if (MatInfo.bAnimatedTexture_Specular)
	{
		EditorMatName += FString("SP");
	}

	if (!EditorMatName.EndsWith(FString("_")))
	{
		EditorMatName += "_";
	}

	EditorMatName += "mat";

	return EditorMatName;
}

EMyFbxModelType UMyFbxProcessor::GetMyFbxModelType(const FString & FilePath_MyFbxXml)
{
	if (FilePath_MyFbxXml.Contains("/Model/MapObject/"))
	{
		return EMyFbxModelType::MapObject;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/Monster/"))
	{
		return EMyFbxModelType::Monster;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/Player/hf/"))
	{
		return EMyFbxModelType::Female;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/Player/hm/"))
	{
		return EMyFbxModelType::Male;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/Ride/"))
	{
		return EMyFbxModelType::Ride;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/Sky/"))
	{
		return EMyFbxModelType::Sky;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/weapons/"))
	{
		return EMyFbxModelType::Weapon;
	}
	else if (FilePath_MyFbxXml.Contains("/Model/NPC/"))
	{
		return EMyFbxModelType::NPC;
	}
	else if (FilePath_MyFbxXml.Contains("/SFX/"))
	{
		return EMyFbxModelType::SFX;
	}

	return EMyFbxModelType::Unknown;
}

void UMyFbxProcessor::AddError(const FString & ErrorMessage)
{
	TArray<FString> OldErrorsArray;
	FFileHelper::LoadFileToStringArray(OldErrorsArray, *UMyFbxProcessor::FilePath_ErrorFile);

	if (!OldErrorsArray.Contains(ErrorMessage))
	{
		OldErrorsArray.Add(ErrorMessage);
	}

	FFileHelper::SaveStringArrayToFile(OldErrorsArray, *UMyFbxProcessor::FilePath_ErrorFile);

}

bool UMyFbxProcessor::AreMaterialInstanceParametersSame(UMaterialInstanceConstant * MIConstant, FMyFbxMatInfo MatInfo)
{
	FString MatInfoParentName = UMyFbxProcessor::GetEditorMatName(MatInfo);
	FString MIConstantParentName = MIConstant->Parent->GetName();

	if (MIConstantParentName == MatInfoParentName)
	{
		if (MatInfo.bMaterialType_TwoSided != MIConstant->TwoSided)
		{
			return false;
		}

		for (FTextureParameterValue& TPV : MIConstant->TextureParameterValues)
		{
			if (TPV.ParameterInfo.Name == FName("Diffuse"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_DiffuseMap)
				{
					return false;
				}
			}
			else if (TPV.ParameterInfo.Name == FName("Specular"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_SpecularMap)
				{
					return false;
				}
			}
			else if (TPV.ParameterInfo.Name == FName("Normal"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_NormalMap)
				{
					return false;
				}
			}
			else if (TPV.ParameterInfo.Name == FName("Glow"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_SelfIlluminationMap)
				{
					return false;
				}
			}
			else if (TPV.ParameterInfo.Name == FName("OpacityMask"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_OpacityMap)
				{
					return false;
				}
			}
			else if (TPV.ParameterInfo.Name == FName("ReflectMap"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_ReflectMap)
				{
					return false;
				}
			}
			else if (TPV.ParameterInfo.Name == FName("SSSMask"))
			{
				if (!TPV.ParameterValue || TPV.ParameterValue->GetName() != MatInfo.Texture_SSSMask)
				{
					return false;
				}
			}
		}

		for (FScalarParameterValue& SPV : MIConstant->ScalarParameterValues)
		{
			if ((SPV.ParameterInfo.Name == FName("GlowIntensity")) && (SPV.ParameterValue != MatInfo.Scalar_SelfIllusionScale))
			{
				return false;
			}
		}

	}
	else
	{
		// If MIConstant parent name and MatInfo mat name are different, return false
		return false;
	}

	return true;
}

void UMyFbxProcessor::ParseMyFbxXmlForMaterials(const FString & FilePath_MyFbxXml, TMap<FString, FMyFbxMatInfo>& OutMap_MyFbxMatsInfo)
{
	FXmlFile MyFbxXmlFileObj(FilePath_MyFbxXml);
	FXmlNode* RootNode = MyFbxXmlFileObj.GetRootNode();
	TArray<FXmlNode*> ChildrenNodes;				// for holding temporary children nodes

	ChildrenNodes = RootNode->GetChildrenNodes();
	TArray<FXmlNode*> Xml_MATERIALLISTs;
	for (FXmlNode* ChildNode : ChildrenNodes)
	{
		if (ChildNode->GetTag() == FString("MATERIALLIST"))
		{
			Xml_MATERIALLISTs.Add(ChildNode);
		}
	}

	TArray<FXmlNode*> Xml_MATERIALs;
	for (FXmlNode* Xml_MATERIALLIST : Xml_MATERIALLISTs)
	{
		ChildrenNodes = Xml_MATERIALLIST->GetChildrenNodes();
		for (FXmlNode* ChildNode : ChildrenNodes)
		{
			if (ChildNode->GetTag() == FString("MATERIAL"))
			{
				Xml_MATERIALs.Add(ChildNode);
			}
		}
	}

	for (FXmlNode* Xml_MATERIAL : Xml_MATERIALs)
	{
		// FMyFbxMaterialInfo MatInfo;
		FMyFbxMatInfo MatInfo;
		FString MatName = Xml_MATERIAL->GetAttribute(FString("name"));

		// Sanitizing mat name is very important, otherwise mat name won't match.
		MatName = ObjectTools::SanitizeObjectName(MatName);

		// ChildrenNodes = Xml_MATERIAL->GetChildrenNodes();
		FXmlNode* Xml_TEXTURELIST = Xml_MATERIAL->FindChildNode(FString("TEXTURELIST"));

		if (Xml_TEXTURELIST)
		{
			FXmlNode* Xml_TexAnimationNode = Xml_TEXTURELIST->FindChildNode(FString("TEX_ANIMATION"));
			if (Xml_TexAnimationNode)
			{
				MatInfo.bAnimatedTexture_AllTextures = true;
			}

			ChildrenNodes = Xml_TEXTURELIST->GetChildrenNodes();
			TArray<FXmlNode*> Xml_TEXTURELAYERs;

			for (FXmlNode* ChildNode : ChildrenNodes)
			{
				if (ChildNode->GetTag() == FString("TEXTURELAYER"))
				{
					Xml_TEXTURELAYERs.Add(ChildNode);
				}
			}

			for (FXmlNode* Xml_TEXTURELAYER : Xml_TEXTURELAYERs)
			{
				FXmlNode* Xml_MAPCHANNEL = Xml_TEXTURELAYER->FindChildNode(FString("MAPCHANNEL"));
				if (Xml_MAPCHANNEL)
				{
					// skip if MAPCHANNEL node is present
					continue;
				}

				FXmlNode* Xml_TEXANIMATION = Xml_TEXTURELAYER->FindChildNode(FString("TEX_ANIMATION"));

				FXmlNode* Xml_DIFFUSEMAP = Xml_TEXTURELAYER->FindChildNode(FString("DIFFUSEMAP"));
				FXmlNode* Xml_SPECULARMAP = Xml_TEXTURELAYER->FindChildNode(FString("SPECULARMAP"));
				FXmlNode* Xml_NORMALMAP = Xml_TEXTURELAYER->FindChildNode(FString("NORMALMAP"));
				FXmlNode* Xml_SELFILLUMINATIONMAP = Xml_TEXTURELAYER->FindChildNode(FString("SELFILLUMINATIONMAP"));
				FXmlNode* Xml_OPACITYMAP = Xml_TEXTURELAYER->FindChildNode(FString("OPACITYMAP"));
				FXmlNode* Xml_REFLECTMAP = Xml_TEXTURELAYER->FindChildNode(FString("REFLECTMAP"));
				FXmlNode* Xml_GLOSSMAP = Xml_TEXTURELAYER->FindChildNode(FString("GLOSSINESS"));
				FXmlNode* Xml_SSSMask = Xml_TEXTURELAYER->FindChildNode(FString("FAKE_SSS_MASK"));

				if (Xml_DIFFUSEMAP)
				{
					MatInfo.Texture_DiffuseMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_DIFFUSEMAP);

					if (Xml_TEXANIMATION)
					{
						MatInfo.bAnimatedTexture_Diffuse = true;
					}
				}

				if (Xml_SPECULARMAP)
				{
					MatInfo.Texture_SpecularMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_SPECULARMAP);

					if (Xml_TEXANIMATION)
					{
						MatInfo.bAnimatedTexture_Specular = true;
					}
				}

				if (Xml_NORMALMAP)
				{
					MatInfo.Texture_NormalMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_NORMALMAP);

					if (Xml_TEXANIMATION)
					{
						MatInfo.bAnimatedTexture_Normal = true;
					}
				}

				if (Xml_SELFILLUMINATIONMAP)
				{
					MatInfo.Texture_SelfIlluminationMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_SELFILLUMINATIONMAP);

					if (Xml_TEXANIMATION)
					{
						MatInfo.bAnimatedTexture_Glow = true;
					}
				}

				if (Xml_OPACITYMAP)
				{
					MatInfo.Texture_OpacityMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_OPACITYMAP);

					if (MatInfo.Texture_OpacityMap.EndsWith(TEXT("_m")) || MatInfo.Texture_OpacityMap.EndsWith(TEXT("_M")) ||
						MatInfo.Texture_OpacityMap.EndsWith(TEXT("_s")))
						// MatInfo.Texture_OpacityMap.EndsWith(TEXT("_s")) || MatInfo.Texture_OpacityMap.EndsWith(TEXT("_sp")))
					{
						MatInfo.bOpacityMaskChannel_Alpha = false;
					}

					if (Xml_TEXANIMATION)
					{
						MatInfo.bAnimatedTexture_Opacity = true;
					}
				}

				if (Xml_REFLECTMAP)
				{
					MatInfo.Texture_ReflectMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_REFLECTMAP);
				}

				if (Xml_GLOSSMAP)
				{
					MatInfo.Texture_GlossMap = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_GLOSSMAP);
				}

				if (Xml_SSSMask)
				{
					MatInfo.Texture_SSSMask = UMyFbxProcessor::GetTextureNameFromXmlNode(Xml_SSSMask);
				}
			}
		}

		FXmlNode* Xml_Ambient = Xml_MATERIAL->FindChildNode(FString("AMBIENT"));
		if (Xml_Ambient)
		{
			TArray<FString> StringArray;
			FString AmbientString = Xml_Ambient->GetContent();
			AmbientString.ParseIntoArray(StringArray, TEXT(" "));
			float Ambient_X = FCString::Atof(*StringArray[0]);
			float Ambient_Y = FCString::Atof(*StringArray[1]);
			float Ambient_Z = FCString::Atof(*StringArray[2]);

			MatInfo.Vector_Ambient = FVector(Ambient_X / 255.f, Ambient_Y / 255.f, Ambient_Z / 255.f);
		}

		FXmlNode* Xml_Diffuse = Xml_MATERIAL->FindChildNode(FString("DIFFUSE"));
		if (Xml_Diffuse)
		{
			TArray<FString> StringArray;
			FString DiffuseString = Xml_Diffuse->GetContent();
			DiffuseString.ParseIntoArray(StringArray, TEXT(" "));
			float Diffuse_X = FCString::Atof(*StringArray[0]);
			float Diffuse_Y = FCString::Atof(*StringArray[1]);
			float Diffuse_Z = FCString::Atof(*StringArray[2]);

			MatInfo.Vector_Diffuse = FVector(Diffuse_X / 255.f, Diffuse_Y / 255.f, Diffuse_Z / 255.f);
		}

		FXmlNode* Xml_Specular = Xml_MATERIAL->FindChildNode(FString("SPECULAR"));
		if (Xml_Specular)
		{
			TArray<FString> StringArray;
			FString SpecularString = Xml_Specular->GetContent();
			SpecularString.ParseIntoArray(StringArray, TEXT(" "));
			float Specular_X = FCString::Atof(*StringArray[0]);
			float Specular_Y = FCString::Atof(*StringArray[1]);
			float Specular_Z = FCString::Atof(*StringArray[2]);

			MatInfo.Vector_Specular = FVector(Specular_X / 255.f, Specular_Y / 255.f, Specular_Z / 255.f);
		}

		FXmlNode* Xml_TWOSIDED = Xml_MATERIAL->FindChildNode(FString("TWOSIDED"));
		if (Xml_TWOSIDED)
		{
			MatInfo.bMaterialType_TwoSided = true;
		}

		FXmlNode* Xml_USEOPACITY = Xml_MATERIAL->FindChildNode(FString("USEOPACITY"));
		if (Xml_USEOPACITY)
		{
			MatInfo.bOpacityBlendModel_Translucent = true;
		}

		FXmlNode* Xml_SpecularLevel = Xml_MATERIAL->FindChildNode(FString("SPECULAR_LEVEL"));
		if (Xml_SpecularLevel)
		{
			MatInfo.Scalar_SpecularLevel = FCString::Atof(*Xml_SpecularLevel->GetContent());
		}

		FXmlNode* Xml_SelfIllusionScale = Xml_MATERIAL->FindChildNode(FString("SELFILLUSIONSCALE"));
		if (Xml_SelfIllusionScale)
		{
			MatInfo.Scalar_SelfIllusionScale = FCString::Atof(*Xml_SelfIllusionScale->GetContent());
		}

		FXmlNode* Xml_Glossiness = Xml_MATERIAL->FindChildNode(FString("GLOSSINESS"));
		if (Xml_Glossiness)
		{
			MatInfo.Scalar_Glossiness = FCString::Atof(*Xml_Glossiness->GetContent());
		}

		FXmlNode* Xml_FAKESSS = Xml_MATERIAL->FindChildNode(FString("FAKE_SSS"));
		if (Xml_FAKESSS)
		{
			if (FilePath_MyFbxXml.Contains("hf_face_"))
			{
				MatInfo.bMaterialType_HumanFace = true;
			}
			else
			{
				MatInfo.bMaterialType_HumanBody = true;
			}
		}

		OutMap_MyFbxMatsInfo.Add(MatName, MatInfo);
	}
}

bool UMyFbxProcessor::FillMaterialInstanceTextureParameter(UMaterialInstanceConstant * MIConstant, FName ParamName, FName TextureName)
{
	FString LogMessage;

	if (AssetDataMap_Textures.Contains(TextureName))
	{
		FTextureParameterValue TexParam;
		TexParam.ParameterInfo.Name = ParamName;
		TexParam.ParameterValue = Cast<UTexture>(AssetDataMap_Textures[TextureName].GetAsset());
		MIConstant->TextureParameterValues.Add(TexParam);
		return true;
	}
	else
	{
		LogMessage = FString("Couldn't find the texture: ") + TextureName.ToString() +
			FString(", required by parameter: ") + ParamName.ToString() + FString(", on material instance: ") +
			MIConstant->GetName();
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
		return false;
	}
}

bool UMyFbxProcessor::FillMaterialInstanceParameters(UMaterialInstanceConstant * MIConstant, const FString & EditorMatName, const FMyFbxMatInfo & MatInfo)
{
	FString LogMessage;
	LogMessage = FString("Filling material instance parameters for material instance: ") + MIConstant->GetName();
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);

	if (!IsValid(MIConstant))
	{
		return false;
	}

	if (EditorMatName == FString("Face_mat"))
	{
		if (!MatInfo.Texture_DiffuseMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Diffuse"), FName(*MatInfo.Texture_DiffuseMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `Diffuse` (Face_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}

		if (!MatInfo.Texture_SpecularMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Specular"), FName(*MatInfo.Texture_SpecularMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `Specular` (Face_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}

		if (!MatInfo.Texture_NormalMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Normal"), FName(*MatInfo.Texture_NormalMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `Normal` (Face_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}

		if (!MatInfo.Texture_OpacityMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("OpacityMask"), FName(*MatInfo.Texture_OpacityMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `OpacityMask` (Face_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}

		if (!MatInfo.Texture_SSSMask.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("SSSMask"), FName(*MatInfo.Texture_SSSMask));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `SSSMask` (Face_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}
	}
	else if (EditorMatName == FString("Body_mat"))
	{
		if (!MatInfo.Texture_DiffuseMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Diffuse"), FName(*MatInfo.Texture_DiffuseMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `Diffuse` (Body_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}

		if (!MatInfo.Texture_SpecularMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Specular"), FName(*MatInfo.Texture_SpecularMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `Specular` (Body_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}

		if (!MatInfo.Texture_NormalMap.IsEmpty())
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Normal"), FName(*MatInfo.Texture_NormalMap));
			if (!bResult)
			{
				return bResult;
			}
		}
		else
		{
			LogMessage = FString("Required texture parameter `Normal` (Body_mat) is missing. Cancelling parameter fill");
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			return false;
		}
	}
	else
	{
		if (MatInfo.bMaterialType_TwoSided)
		{
			MIConstant->BasePropertyOverrides.bOverride_TwoSided = true;
			MIConstant->BasePropertyOverrides.TwoSided = true;
		}

		if (EditorMatName.Contains(TEXT("D")))
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Diffuse"), FName(*MatInfo.Texture_DiffuseMap));
			if (!bResult)
			{
				return bResult;
			}
		}

		if (EditorMatName.Contains(TEXT("S")))
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Specular"), FName(*MatInfo.Texture_SpecularMap));
			if (!bResult)
			{
				return bResult;
			}
		}

		if (EditorMatName.Contains(TEXT("N")))
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Normal"), FName(*MatInfo.Texture_NormalMap));
			if (!bResult)
			{
				return bResult;
			}
		}

		if (EditorMatName.Contains(TEXT("G")))
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("Glow"), FName(*MatInfo.Texture_SelfIlluminationMap));
			if (!bResult)
			{
				return bResult;
			}

			FScalarParameterValue GlowIntensityParamValue;
			GlowIntensityParamValue.ParameterInfo.Name = FName("GlowIntensity");
			GlowIntensityParamValue.ParameterValue = MatInfo.Scalar_SelfIllusionScale;
			MIConstant->ScalarParameterValues.Add(GlowIntensityParamValue);
		}

		// Intentionally case sensetive as "T" conflicts with "t" in "_mat"
		if (EditorMatName.Contains(TEXT("TA"), ESearchCase::CaseSensitive) ||
			EditorMatName.Contains(TEXT("T"), ESearchCase::CaseSensitive) ||
			EditorMatName.Contains(TEXT("LA"), ESearchCase::CaseSensitive) ||
			EditorMatName.Contains(TEXT("L"), ESearchCase::CaseSensitive))
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("OpacityMask"), FName(*MatInfo.Texture_OpacityMap));
			if (!bResult)
			{
				return bResult;
			}
		}

		if (EditorMatName.Contains(TEXT("RA")))
		{
			bool bResult = FillMaterialInstanceTextureParameter(MIConstant, FName("ReflectMap"), FName(*MatInfo.Texture_ReflectMap));
			if (!bResult)
			{
				return bResult;
			}
		}
	}

	return true;
}

EImportResult UMyFbxProcessor::CreateAndApplyStaticMeshMaterials(UStaticMesh * StaticMesh, TMap<FString, FMyFbxMatInfo> Map_MyFbxMatsInfo)
{
	FString LogMessage;
	FString DialogMessage;
	FText DialogText;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	if (!IsValid(StaticMesh))
	{
		return EImportResult::Failure;
	}

	for (FStaticMaterial& Mat : StaticMesh->StaticMaterials)
	{
		FString MatName = Mat.MaterialSlotName.ToString();
		
		if (!Map_MyFbxMatsInfo.Contains(MatName))
		{
			LogMessage = FString("Couldn't find a material named `") + MatName +
				FString("` on static mesh: `") + StaticMesh->GetName() + FString("`");
			UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

			LogMessage = FString("Attempting to fix material name. Material name changed from ") + MatName;

			for (TPair<FString, FMyFbxMatInfo> MyFbxMatInfoPair : Map_MyFbxMatsInfo)
			{
				if (MyFbxMatInfoPair.Key.Len() >= 64)
				{
					FString NewKey = UKismetStringLibrary::GetSubstring(MyFbxMatInfoPair.Key, 0, 63);
					if (NewKey == MatName)
					{
						Map_MyFbxMatsInfo.Remove(MyFbxMatInfoPair.Key);
						Map_MyFbxMatsInfo.Add(NewKey, MyFbxMatInfoPair.Value);
						UE_LOG(LogTemp, Warning, TEXT("Newkey is same as matname"));
					}
				}
				/*
				 The following code sometimes causes a bug and returns false for Map.Contains()
				// for (TPair<FString, FMyFbxMatInfo>& MyFbxMatInfoPair : Map_MyFbxMatsInfo)
				if (MyFbxMatInfoPair.Key.Len() >= 64)
				{
					MyFbxMatInfoPair.Key = UKismetStringLibrary::GetSubstring(MyFbxMatInfoPair.Key, 0, 63);
					UE_LOG(LogTemp, Warning, TEXT("Changed MyFbxMatInfoPair.Key"), *MyFbxMatInfoPair.Key);

					UE_LOG(LogTemp, Warning, TEXT("%s"), *MyFbxMatInfoPair.Key);
					UE_LOG(LogTemp, Warning, TEXT("%s"), *MatName);
				}
				*/

				if (MatName.Contains(MyFbxMatInfoPair.Key))
				{
					FString TrailingNumbers = MatName.Replace(*MyFbxMatInfoPair.Key, TEXT(""));
					if (TrailingNumbers.StartsWith(FString("_")))
					{
						MatName = MyFbxMatInfoPair.Key;
						break;
					}
				}
			}
			
			LogMessage += FString(" to ") + MatName;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		}

		// Cannot use contains here. It gives false result sometimes. [https://answers.unrealengine.com/questions/459188/tmapcontains-returns-false-for-an-existing-key.html]
		if (Map_MyFbxMatsInfo.Contains(MatName))
		{
			FMyFbxMatInfo MatInfo = Map_MyFbxMatsInfo[MatName];
			FString MIConstantName = FString("MI_") + MatName;
			FString MIPackageName = UMyFbxProcessor::EditorDir_MaterialInstances + FString("/") + MIConstantName;

			UPackage* MIPackage = nullptr;
			UMaterialInstanceConstant* MIConstant = nullptr;

			bool bCreateNewMatConstant = true;

			if (FPackageName::DoesPackageExist(MIPackageName))
			{
				LogMessage = FString("Material Instance package already exists: ") + MIPackageName;
				UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

				MIPackage = LoadPackage(nullptr, *MIPackageName, LOAD_None);
				if (MIPackage)
				{
					LogMessage = FString("Attempting to load material instance from existing package...");
					UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);

					MIPackage->FullyLoad();
					MIConstant = Cast<UMaterialInstanceConstant>(StaticFindObject(UMaterialInstanceConstant::StaticClass(), MIPackage, *MIConstantName));
					if (MIConstant)
					{
						LogMessage = FString("Existing material instance found and loaded. Checking if the existing material instance contains different parameters...");
						UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);


						bool bResult = UMyFbxProcessor::AreMaterialInstanceParametersSame(MIConstant, MatInfo);
						if (bResult)
						{
							LogMessage = FString("Existing material instance parameters are same. Using the same material instance on current mesh.");
							UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
							bCreateNewMatConstant = false;
						}
						else
						{
							LogMessage = FString("Existing material instance parameters are different. Creating a new material instance now.");
							UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
							MIConstant = nullptr;
							MIConstantName = FString("MI_") + MatName + FString("_") + StaticMesh->GetName();
							MIPackageName = UMyFbxProcessor::EditorDir_MaterialInstances + FString("/") + MIConstantName;
						}
					}
					else
					{
						LogMessage = FString("Couldn't find material instance in existing package: ") + MIPackageName + FString(". This shouldn't happen.");
						DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
						DialogText = FText::FromString(DialogMessage);
						EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

						UMyFbxProcessor::AddError(LogMessage);

						if (AppReturnType == EAppReturnType::Yes)
						{
							return EImportResult::Cancelled;
						}
					}
				}
				else
				{
					LogMessage = FString("Couldn't load the existing material package. Attempting to create a new material package now.");
					UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
				}
			}

			if (bCreateNewMatConstant)
			{
				MIPackage = CreatePackage(nullptr, *MIPackageName);
				MIPackage->FullyLoad();

				FString EditorMatName = UMyFbxProcessor::GetEditorMatName(MatInfo);
				UMaterial* BaseMaterial = nullptr;

				if (AssetDataMap_SimpleMaterials.Contains(FName(*EditorMatName)))
				{
					BaseMaterial = Cast<UMaterial>(AssetDataMap_SimpleMaterials[FName(*EditorMatName)].GetAsset());
				}
				else if (AssetDataMap_HumanSkinMaterials.Contains(FName(*EditorMatName)))
				{
					BaseMaterial = Cast<UMaterial>(AssetDataMap_HumanSkinMaterials[FName(*EditorMatName)].GetAsset());
				}

				if (BaseMaterial)
				{
					MIConstantFactoryNew->InitialParent = BaseMaterial;
					MIConstant = Cast<UMaterialInstanceConstant>(MIConstantFactoryNew->FactoryCreateNew(UMaterialInstanceConstant::StaticClass(), MIPackage, FName(*MIConstantName), EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, nullptr, GWarn));
					AssetRegistryModule.AssetCreated(MIConstant);
				}
				else
				{
					LogMessage = FString("Couldn't find the base material named `") + EditorMatName + FString("` needed for material instance `") +
						MIConstantName + FString("` on static mesh: ") + StaticMesh->GetName();
					DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
					DialogText = FText::FromString(DialogMessage);
					EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

					UMyFbxProcessor::AddError(LogMessage);

					if (AppReturnType == EAppReturnType::Yes)
					{
						return EImportResult::Cancelled;
					}
				}
			}

			if (MIConstant)
			{
				FString ParentMatName = MIConstant->Parent->GetName();
				bool bResult = UMyFbxProcessor::FillMaterialInstanceParameters(MIConstant, ParentMatName, MatInfo);

				if (!bResult)
				{
					LogMessage = FString("Some error occured while filling materials for static mesh : ") + StaticMesh->GetName();
					DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
					DialogText = FText::FromString(DialogMessage);
					EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

					if (AppReturnType == EAppReturnType::Yes)
					{
						return EImportResult::Cancelled;
					}
				}

				Mat.MaterialInterface = MIConstant;
				MIConstant->PostEditChange();

				MIConstant->MarkPackageDirty();
				
				/*
					@NOTE  It's very very important to save material instance package on disk, 
					otherwise FPackageName::DoesPackageExist(MIPackageName) won't be able to detect package.
				*/
				FString FullPackagePath = FPaths::ProjectContentDir() + MIPackageName.Replace(TEXT("/Game/"), TEXT(""));

				UPackage::SavePackage(MIPackage, nullptr, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
									  *(FullPackagePath + FPackageName::GetAssetPackageExtension()));
			}
		}
		else
		{
			LogMessage = FString("Couldn't find a material named `") + MatName + FString("` on static mesh: `") + StaticMesh->GetName();
			DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
			DialogText = FText::FromString(DialogMessage);
			EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);
			
			UMyFbxProcessor::AddError(LogMessage);

			if (AppReturnType == EAppReturnType::Yes)
			{
				return EImportResult::Cancelled;
			}
		}
	}

	return EImportResult::Success;
}

EImportResult UMyFbxProcessor::CreateAndApplySkeletalMeshMaterials(USkeletalMesh * SkeletalMesh, TMap<FString, FMyFbxMatInfo> Map_MyFbxMatsInfo)
{
	FString LogMessage;
	FString DialogMessage;
	FText DialogText;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	if (!IsValid(SkeletalMesh))
	{
		return EImportResult::Failure;
	}

	for (FSkeletalMaterial& Mat : SkeletalMesh->Materials)
	{
		FString MatName = Mat.MaterialSlotName.ToString();

		if (!Map_MyFbxMatsInfo.Contains(MatName))
		{
			LogMessage = FString("Couldn't find a material named `") + MatName +
				FString("` on skeletal mesh: `") + SkeletalMesh->GetName() + FString("`");
			UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

			LogMessage = FString("Attempting to fix material name. Material name changed from ") + MatName;

			for (TPair<FString, FMyFbxMatInfo> MyFbxMatInfoPair : Map_MyFbxMatsInfo)
			{
				if (MyFbxMatInfoPair.Key.Len() >= 64)
				{
					FString NewKey = UKismetStringLibrary::GetSubstring(MyFbxMatInfoPair.Key, 0, 63);
					if (NewKey == MatName)
					{
						Map_MyFbxMatsInfo.Remove(MyFbxMatInfoPair.Key);
						Map_MyFbxMatsInfo.Add(NewKey, MyFbxMatInfoPair.Value);
					}
				}
				/*
				The following code sometimes causes a bug and returns false for Map.Contains()
				// for (TPair<FString, FMyFbxMatInfo>& MyFbxMatInfoPair : Map_MyFbxMatsInfo)
				if (MyFbxMatInfoPair.Key.Len() >= 64)
				{
				MyFbxMatInfoPair.Key = UKismetStringLibrary::GetSubstring(MyFbxMatInfoPair.Key, 0, 63);
				UE_LOG(LogTemp, Warning, TEXT("Changed MyFbxMatInfoPair.Key"), *MyFbxMatInfoPair.Key);

				UE_LOG(LogTemp, Warning, TEXT("%s"), *MyFbxMatInfoPair.Key);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *MatName);
				}
				*/

				if (MatName.Contains(MyFbxMatInfoPair.Key))
				{
					FString TrailingNumbers = MatName.Replace(*MyFbxMatInfoPair.Key, TEXT(""));
					if (TrailingNumbers.StartsWith(FString("_")))
					{
						MatName = MyFbxMatInfoPair.Key;
						break;
					}
				}
			}
			LogMessage += FString(" to ") + MatName;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
		}

		if (Map_MyFbxMatsInfo.Contains(MatName))
		{
			FMyFbxMatInfo MatInfo = Map_MyFbxMatsInfo[MatName];
			FString MIConstantName = FString("MI_") + MatName;
			FString MIPackageName = UMyFbxProcessor::EditorDir_MaterialInstances + FString("/") + MIConstantName;

			UPackage* MIPackage = nullptr;
			UMaterialInstanceConstant* MIConstant = nullptr;

			bool bCreateNewMatConstant = true;

			if (FPackageName::DoesPackageExist(MIPackageName))
			{
				LogMessage = FString("Material Instance package already exists: ") + MIPackageName;
				UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

				MIPackage = LoadPackage(nullptr, *MIPackageName, LOAD_None);
				if (MIPackage)
				{
					LogMessage = FString("Attempting to load material instance from existing package...");
					UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);

					MIPackage->FullyLoad();
					MIConstant = Cast<UMaterialInstanceConstant>(StaticFindObject(UMaterialInstanceConstant::StaticClass(), MIPackage, *MIConstantName));
					if (MIConstant)
					{
						LogMessage = FString("Existing material instance found and loaded. Checking if the existing material instance contains different parameters...");
						UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);


						bool bResult = UMyFbxProcessor::AreMaterialInstanceParametersSame(MIConstant, MatInfo);
						if (bResult)
						{
							LogMessage = FString("Existing material instance parameters are same. Using the same material instance on current mesh.");
							UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
							bCreateNewMatConstant = false;
						}
						else
						{
							LogMessage = FString("Existing material instance parameters are different. Creating a new material instance now.");
							UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
							MIConstant = nullptr;
							MIConstantName = FString("MI_") + MatName + FString("_") + SkeletalMesh->GetName();
							MIPackageName = UMyFbxProcessor::EditorDir_MaterialInstances + FString("/") + MIConstantName;
						}
					}
					else
					{
						LogMessage = FString("Couldn't find material instance in existing package: ") + MIPackageName + FString(". This shouldn't happen.");
						DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
						DialogText = FText::FromString(DialogMessage);
						EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

						UMyFbxProcessor::AddError(LogMessage);

						if (AppReturnType == EAppReturnType::Yes)
						{
							return EImportResult::Cancelled;
						}
					}
				}
				else
				{
					LogMessage = FString("Couldn't load the existing material package. Attempting to create a new material package now.");
					UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
				}
			}

			if (bCreateNewMatConstant)
			{
				MIPackage = CreatePackage(nullptr, *MIPackageName);
				MIPackage->FullyLoad();

				FString EditorMatName = UMyFbxProcessor::GetEditorMatName(MatInfo);
				UMaterial* BaseMaterial = nullptr;

				if (AssetDataMap_SimpleMaterials.Contains(FName(*EditorMatName)))
				{
					BaseMaterial = Cast<UMaterial>(AssetDataMap_SimpleMaterials[FName(*EditorMatName)].GetAsset());
				}
				else if (AssetDataMap_HumanSkinMaterials.Contains(FName(*EditorMatName)))
				{
					BaseMaterial = Cast<UMaterial>(AssetDataMap_HumanSkinMaterials[FName(*EditorMatName)].GetAsset());
				}

				if (BaseMaterial)
				{
					MIConstantFactoryNew->InitialParent = BaseMaterial;
					MIConstant = Cast<UMaterialInstanceConstant>(MIConstantFactoryNew->FactoryCreateNew(UMaterialInstanceConstant::StaticClass(), MIPackage, FName(*MIConstantName), EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, nullptr, GWarn));
					AssetRegistryModule.AssetCreated(MIConstant);
				}
				else
				{
					LogMessage = FString("Couldn't find the base material named `") + EditorMatName + FString("` needed for material instance `") +
						MIConstantName + FString("` on skeletal mesh: ") + SkeletalMesh->GetName();
					DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
					DialogText = FText::FromString(DialogMessage);
					EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

					UMyFbxProcessor::AddError(LogMessage);

					if (AppReturnType == EAppReturnType::Yes)
					{
						return EImportResult::Cancelled;
					}
				}
			}

			if (MIConstant)
			{
				FString ParentMatName = MIConstant->Parent->GetName();
				bool bResult = UMyFbxProcessor::FillMaterialInstanceParameters(MIConstant, ParentMatName, MatInfo);

				if (!bResult)
				{
					LogMessage = FString("Some error occured while filling materials for skeletal mesh : ") + SkeletalMesh->GetName();
					DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
					DialogText = FText::FromString(DialogMessage);
					EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

					if (AppReturnType == EAppReturnType::Yes)
					{
						return EImportResult::Cancelled;
					}
				}

				Mat.MaterialInterface = MIConstant;
				MIConstant->PostEditChange();

				MIConstant->MarkPackageDirty();

				/*
				@NOTE  It's very very important to save material instance package on disk,
				otherwise FPackageName::DoesPackageExist(MIPackageName) won't be able to detect package.
				*/
				FString FullPackagePath = FPaths::ProjectContentDir() + MIPackageName.Replace(TEXT("/Game/"), TEXT(""));

				UPackage::SavePackage(MIPackage, nullptr, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
									  *(FullPackagePath + FPackageName::GetAssetPackageExtension()));
			}
		}
		else
		{
			LogMessage = FString("Couldn't find a material named `") + MatName + FString("` on skeletal mesh: `") + SkeletalMesh->GetName();
			DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
			DialogText = FText::FromString(DialogMessage);
			EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

			UMyFbxProcessor::AddError(LogMessage);

			if (AppReturnType == EAppReturnType::Yes)
			{
				return EImportResult::Cancelled;
			}
		}
	}

	return EImportResult::Success;
}

EImportResult UMyFbxProcessor::ImportMyFbxModels(const TArray<FString>& InPaths_MyFbxXmlFilesToLoad, TArray<FString>& OutPaths_MyFbxXmlFilesLoaded)
{
	FString DialogMessage;
	FText DialogText;
	FString LogMessage;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	StaticFbxFactory->ResetState();
	SkeletalFbxFactory->ResetState();

	for (const FString& FilePath_MyFbxXml : InPaths_MyFbxXmlFilesToLoad)
	{
		FMyFbxImportFilesInfo MyFbxImportFilesInfo(FilePath_MyFbxXml);
		EMyFbxModelType MyFbxXmlModelType = UMyFbxProcessor::GetMyFbxModelType(FilePath_MyFbxXml);

		// FString DialogMessage_MyFbxXmlInfo = FString("Current MyFbxXmlFile : ") + FilePath_MyFbxXml + FString("\n");

		bool bMaterialImportError = false;

		if (MyFbxXmlModelType == EMyFbxModelType::MapObject ||
			MyFbxXmlModelType == EMyFbxModelType::Monster ||
			MyFbxXmlModelType == EMyFbxModelType::NPC ||
			MyFbxXmlModelType == EMyFbxModelType::Ride ||
			MyFbxXmlModelType == EMyFbxModelType::Sky ||
			MyFbxXmlModelType == EMyFbxModelType::Weapon)
		{
			for (FString& FilePath_MyFbxModel : MyFbxImportFilesInfo.FilePaths_MyFbxModels)
			{
				FString FileName_MyFbxModel = FPaths::GetBaseFilename(FilePath_MyFbxModel);
				FString EditorDir_ModelPackage = MyFbxImportFilesInfo.DirPath_MyFbxObject.Replace(*DirPath_AllModels, *EditorDir_AllModels);

				// FString DialogMessage_ModelInfo = FString("Current Model : ") + FileName_MyFbxModel + FString("\n");

				if (FileName_MyFbxModel.StartsWith(TEXT("S_")))
				{
					// Skip if LOD model number is not -1 or 0
					if (!(FileName_MyFbxModel.Contains(TEXT("_LOD-1")) || FileName_MyFbxModel.Contains(TEXT("_LOD0"))))
					{
						continue;
					}

					EImportResult StaticMeshImportResult;
					UStaticMesh* ImportedStaticMesh = ImportStaticMesh(FilePath_MyFbxModel, EditorDir_ModelPackage, StaticMeshImportResult);
					if (StaticMeshImportResult == EImportResult::Success)
					{
						check(ImportedStaticMesh);

						AssetRegistryModule.AssetCreated(ImportedStaticMesh);
						ImportedStaticMesh->MarkPackageDirty();
						LogMessage = FString("Successfully imported static mesh: ") + FileName_MyFbxModel;
						UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
					}
					else if (StaticMeshImportResult == EImportResult::Cancelled)
					{
						return EImportResult::Cancelled;
					}
					else if (StaticMeshImportResult == EImportResult::Failure)
					{
						LogMessage = FString("Failed to import static mesh: ") + FileName_MyFbxModel;
						UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

						// Do not process mesh any further in case of failure.
						continue;

						/*
						DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
						DialogText = FText::FromString(DialogMessage);
						EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

						if (AppReturnType == EAppReturnType::Yes)
						{
							return EImportResult::Cancelled;
						}
						else
						{
							// Do not process mesh any further in case of failure.
							continue;
						}
						*/
					}

					EImportResult Result = CreateAndApplyStaticMeshMaterials(ImportedStaticMesh, MyFbxImportFilesInfo.Map_MyFbxMatsInfo);
					if (Result == EImportResult::Cancelled)
					{
						return Result;
					}
					else if (Result == EImportResult::Failure)
					{
						bMaterialImportError = true;
					}
				}
				else if (FileName_MyFbxModel.StartsWith(TEXT("SK_")))
				{
					EImportResult SkeletalMeshImportResult;
					USkeletalMesh* ImportedSkeletalMesh = ImportSkeletalMesh(FilePath_MyFbxModel, EditorDir_ModelPackage, SkeletalMeshImportResult);
					if (SkeletalMeshImportResult == EImportResult::Success)
					{
						check(ImportedSkeletalMesh);

						AssetRegistryModule.AssetCreated(ImportedSkeletalMesh);
						ImportedSkeletalMesh->MarkPackageDirty();
						LogMessage = FString("Successfully imported skeletal mesh: ") + FileName_MyFbxModel;
						UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
					}
					else if (SkeletalMeshImportResult == EImportResult::Cancelled)
					{
						return EImportResult::Cancelled;
					}
					else if (SkeletalMeshImportResult == EImportResult::Failure)
					{
						LogMessage = FString("Failed to import skeleltal mesh: ") + FileName_MyFbxModel;
						UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

						// Do not process mesh any further in case of failure.
						continue;
						 
						/*
						DialogMessage = LogMessage + FString("\nDo you want to cancel further import?");
						DialogText = FText::FromString(DialogMessage);
						EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

						if (AppReturnType == EAppReturnType::Yes)
						{
						return EImportResult::Cancelled;
						}
						else
						{
						// Do not process mesh any further in case of failure.
						continue;
						}
						*/
					}

					//~ Import animations
					for (FString& FilePath_Animation : MyFbxImportFilesInfo.FilePaths_MyFbxAnimations)
					{
						FString FileName_Animation = FPaths::GetBaseFilename(FilePath_Animation);
						FString AniPackageName = EditorDir_ModelPackage + FString("/") + FString("ani") + FString("/") + FileName_Animation;
						AniPackageName = PackageTools::SanitizePackageName(AniPackageName);

						LogMessage = FString("Importing animation file: ") + FileName_Animation;
						UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);

						UPackage* AniPackage = nullptr;
						if (FPackageName::DoesPackageExist(AniPackageName))
						{
							FString LogMessage = FString("Animation package for ") + FileName_Animation + FString(" already exists");
							UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
							AniPackage = LoadPackage(nullptr, *AniPackageName, LOAD_None);
							if (AniPackage)
							{
								AniPackage->FullyLoad();
							}
						}
						else
						{
							AniPackage = CreatePackage(nullptr, *AniPackageName);
							AniPackage->FullyLoad();
						}

						UFbxAnimSequenceImportData* Data = NewObject<UFbxAnimSequenceImportData>();
						UEditorEngine::ImportFbxAnimation(ImportedSkeletalMesh->Skeleton, AniPackage, Data, *FilePath_Animation, *FileName_Animation, false);
					}

					EImportResult Result = CreateAndApplySkeletalMeshMaterials(ImportedSkeletalMesh, MyFbxImportFilesInfo.Map_MyFbxMatsInfo);
					if (Result == EImportResult::Cancelled)
					{
						return Result;
					}
					else if (Result == EImportResult::Failure)
					{
						bMaterialImportError = true;
					}
				}
			}
		}
		else if (MyFbxXmlModelType == EMyFbxModelType::Female ||
				MyFbxXmlModelType == EMyFbxModelType::Male)
		{
			for (FString& FilePath_MyFbxModel : MyFbxImportFilesInfo.FilePaths_MyFbxModels)
			{
				FString FileName_MyFbxModel = FPaths::GetBaseFilename(FilePath_MyFbxModel);
				FString EditorDir_ModelPackage = MyFbxImportFilesInfo.DirPath_MyFbxObject.Replace(*DirPath_AllModels, *EditorDir_AllModels);

				// FString DialogMessage_ModelInfo = FString("Current Model : ") + FileName_MyFbxModel + FString("\n");

				if (FileName_MyFbxModel.StartsWith(TEXT("SK_")))
				{
					EImportResult SkeletalMeshImportResult;
					USkeletalMesh* ImportedSkeletalMesh = ImportSkeletalMesh(FilePath_MyFbxModel, EditorDir_ModelPackage, SkeletalMeshImportResult);
					if (SkeletalMeshImportResult == EImportResult::Success)
					{
						check(ImportedSkeletalMesh);

						AssetRegistryModule.AssetCreated(ImportedSkeletalMesh);
						ImportedSkeletalMesh->MarkPackageDirty();
						LogMessage = FString("Successfully imported skeletal mesh: ") + FileName_MyFbxModel;
						UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
					}
					else if (SkeletalMeshImportResult == EImportResult::Cancelled)
					{
						return EImportResult::Cancelled;
					}
					else if (SkeletalMeshImportResult == EImportResult::Failure)
					{
						LogMessage = FString("Failed to import skeleltal mesh: ") + FileName_MyFbxModel;
						UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);

						// Do not process mesh any further in case of failure.
						continue;
					}

					EImportResult Result = CreateAndApplySkeletalMeshMaterials(ImportedSkeletalMesh, MyFbxImportFilesInfo.Map_MyFbxMatsInfo);
					if (Result == EImportResult::Cancelled)
					{
						return Result;
					}
					else if (Result == EImportResult::Failure)
					{
						bMaterialImportError = true;
					}
				}
				else
				{
					DialogMessage = FString("Human model mesh is not a skeletal mesh!");
					DialogText = FText::FromString(DialogMessage);
					EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::Ok, DialogText);
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Load human model animations manually"));
			/*
			//~ Import animations
			DialogMessage = FString("Please import animations for human models manually!");
			DialogText = FText::FromString(DialogMessage);
			EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::Ok, DialogText);
			*/
		}
		else
		{
			DialogMessage = FilePath_MyFbxXml + FString("\nMyFbx model type is currently not supported. Cancelling import!");
			DialogText = FText::FromString(DialogMessage);
			EAppReturnType::Type AppReturnType = FMessageDialog::Open(EAppMsgType::Ok, DialogText);
			// return EImportResult::Failure;
			continue;
		}

		if (bMaterialImportError)
		{
			// Do not add file to Outpaths_MyFbxXmlFilesLoaded
			continue;
		}

		OutPaths_MyFbxXmlFilesLoaded.Add(FilePath_MyFbxXml);
	}

	return EImportResult::Success;
}