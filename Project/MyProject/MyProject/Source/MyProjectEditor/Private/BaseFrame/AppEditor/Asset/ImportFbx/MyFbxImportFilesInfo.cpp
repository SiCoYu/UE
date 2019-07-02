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

FMyFbxImportFilesInfo::FMyFbxImportFilesInfo(const FString & FilePath_MyFbxXml)
{
	IFileManager& FileManager = IFileManager::Get();

	this->FilePath_MyFbxXml = FilePath_MyFbxXml;
	FString XmlDirPath = FPaths::GetPath(FilePath_MyFbxXml);

	this->DirPath_MyFbxObject = FPaths::GetPath(XmlDirPath);
	this->DirName_MyFbxObject = FPaths::GetBaseFilename(this->DirPath_MyFbxObject);

	FString MyFbxModelDirPath = this->DirPath_MyFbxObject + FString("/") + UMyFbxProcessor::DirName_MyFbxModels;
	TArray<FString> FileNames_MyFbxModels;

	FileManager.FindFiles(FileNames_MyFbxModels, *MyFbxModelDirPath, *FString("fbx"));

	for (FString& MyFbxModelFileName : FileNames_MyFbxModels)
	{
		FString MyFbxModelFilePath = MyFbxModelDirPath + FString("/") + MyFbxModelFileName;
		this->FilePaths_MyFbxModels.Add(MyFbxModelFilePath);
	}

	FileNames_MyFbxModels.Empty();

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

	FString DirPath_MyFbxAnimations = this->DirPath_MyFbxObject + FString("/") + UMyFbxProcessor::DirName_MyFbxAnimations;
	TArray<FString> FileNames_MyFbxAnimations;

	FileManager.FindFiles(FileNames_MyFbxAnimations, *DirPath_MyFbxAnimations, *FString("fbx"));

	for (FString& FileName_MyFbxAnimation: FileNames_MyFbxAnimations)
	{
		FString FilePath_MyFbxAnimation = DirPath_MyFbxAnimations + FString("/") + FileName_MyFbxAnimation;
		this->FilePaths_MyFbxAnimations.Add(FilePath_MyFbxAnimation);
	}

	FileNames_MyFbxAnimations.Empty();

	UMyFbxProcessor::ParseMyFbxXmlForMaterials(this->FilePath_MyFbxXml, this->Map_MyFbxMatsInfo);

}