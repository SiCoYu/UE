#include "MyFbxImportFilesInfo.h"
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

FMyFbxImportFilesInfo::FMyFbxImportFilesInfo(const FString & FilePath_EluXml)
{
	IFileManager& FileManager = IFileManager::Get();

	this->FilePath_EluXml = FilePath_EluXml;
	FString XmlDirPath = FPaths::GetPath(FilePath_EluXml);

	this->DirPath_EluObject = FPaths::GetPath(XmlDirPath);
	this->DirName_EluObject = FPaths::GetBaseFilename(this->DirPath_EluObject);

	FString EluModelDirPath = this->DirPath_EluObject + FString("/") + UMyFbxProcessor::DirName_EluModels;
	TArray<FString> FileNames_EluModels;

	FileManager.FindFiles(FileNames_EluModels, *EluModelDirPath, *FString("fbx"));

	for (FString& EluModelFileName : FileNames_EluModels)
	{
		FString EluModelFilePath = EluModelDirPath + FString("/") + EluModelFileName;
		this->FilePaths_EluModels.Add(EluModelFilePath);
	}

	FileNames_EluModels.Empty();

	TArray<FString> FileNames_Xml;
	FileManager.FindFiles(FileNames_Xml, *XmlDirPath, *FString("xml"));

	for (FString& FileName_Xml : FileNames_Xml)
	{
		// Base xml file name without .xml extension
		const FString& XmlBaseFileName = FPaths::GetBaseFilename(FileName_Xml);
		// Get the second extension from FileName_Xml, e.g., if FileName_Xml = test.animation.xml then BaseFileNameExtension = "animation"
		const FString& BaseFileNameExtension = FPaths::GetExtension(XmlBaseFileName);

		if (BaseFileNameExtension == FString("animation"))
		{
			this->FilePath_AnimationXml = XmlDirPath + FString("/") + FileName_Xml;
		}
		else if (BaseFileNameExtension == FString("animationevent"))
		{
			this->FilePath_AnimationEventXml = XmlDirPath + FString("/") + FileName_Xml;
		}
		else if (BaseFileNameExtension == FString("animationInfo"))
		{
			this->FilePath_AnimationInfoXml = XmlDirPath + FString("/") + FileName_Xml;
		}
		else if (BaseFileNameExtension == FString("animationsoundevent"))
		{
			this->FilePath_AnimationSoundEventXml = XmlDirPath + FString("/") + FileName_Xml;
		}
		else if (BaseFileNameExtension == FString("scene"))
		{
			this->FilePath_SceneXml = XmlDirPath + FString("/") + FileName_Xml;
		}
		else
		{
			// pass
		}

	}

	FString DirPath_EluAnimations = this->DirPath_EluObject + FString("/") + UMyFbxProcessor::DirName_EluAnimations;
	TArray<FString> FileNames_EluAnimations;

	FileManager.FindFiles(FileNames_EluAnimations, *DirPath_EluAnimations, *FString("fbx"));

	for (FString& FileName_EluAnimation: FileNames_EluAnimations)
	{
		FString FilePath_EluAnimation = DirPath_EluAnimations + FString("/") + FileName_EluAnimation;
		this->FilePaths_EluAnimations.Add(FilePath_EluAnimation);
	}

	FileNames_EluAnimations.Empty();

	UMyFbxProcessor::ParseEluXmlForMaterials(this->FilePath_EluXml, this->Map_EluMatsInfo);

}