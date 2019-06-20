#include "MyProjectEditor.h"
#include "TestAsset.h"
#include "MyAssetRegistry.h"
#include "Ctx.h"
#include "UObject/NameTypes.h"	// FName
#include "Containers/Array.h"	// TArray
#include "Misc/AssetRegistryInterface.h"	// EAssetRegistryDependencyType
#include "AssetData.h"	// FAssetData
#include "Engine/Texture2D.h"		// UTexture2D 

#include "WidgetBlueprint.h"		// Engine\Source\Editor\UMGEditor\Public\WidgetBlueprint.h, UWidgetBlueprint
#include "PaperFlipbook.h"   // Engine\Plugins\2D\Paper2D\Source\Paper2D\Classes\PaperFlipbook.h, UPaperFlipbook

MY_BEGIN_NAMESPACE(MyNS)

void TestAsset::run()
{
	this->_testDep();
}

void TestAsset::_testDep()
{
	TArray<FName> OutDependencies;
	GMyAssetRegistry->GetDependencies(TEXT("Blueprint'/Game/MyAsset/MyTom/PakTest.PakTest'"), OutDependencies);
}

void TestAsset::_testGetAssetData()
{
	// Engine\Plugins\2D\Paper2D\Source\Paper2DEditor\Private\PaperSpriteFactory.cpp
	// UObject* UPaperSpriteFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
	FString objectPath = TEXT("");

	FAssetData AssetData = GMyAssetRegistry->GetAssetByObjectPath(*objectPath);

	if (AssetData.IsValid())
	{
		if (UTexture2D* NormalMapTexture = Cast<UTexture2D>(AssetData.GetAsset()))
		{

		}
	}
}

// http://www.90cg.com/wordpress/ue4_unreal-asset-loading/
void TestAsset::_testLoadAndPackageName()
{
	{
		FStringAssetReference testAssetRef = " /Game/UMG/NewWidgetBlueprint ";
		UObject* pObject = testAssetRef.TryLoad();
		UWidgetBlueprint* pWidgetBlueprint = Cast<UWidgetBlueprint>(pObject);
		auto widget = CreateWidget<UUserWidget>(this, pWidgetBlueprint->GeneratedClass);
		// do something
		// widget->AddToViewport();
		FString pathName1 = FPackageName::LongPackageNameToFilename(pObject->GetPathName(), FPackageName::GetAssetPackageExtension());
		FString pathName2 = FPackageName::LongPackageNameToFilename(pObject->GetOutermost()->GetPathName(), FPackageName::GetAssetPackageExtension());
	}
	{
		FStringAssetReference testAssetRef = " /Game/UGameAssets/Assets/horizo​​n/Maps/MainMap ";
		UObject* pObject = testAssetRef.TryLoad();
		UWorld* pWorld = Cast<UWorld>(pObject);
		FString pathName1 = FPackageName::LongPackageNameToFilename(pObject->GetPathName(), FPackageName::GetMapPackageExtension());
		FString pathName2 = FPackageName::LongPackageNameToFilename(pObject->GetOutermost()->GetPathName(), FPackageName::GetMapPackageExtension());
	}
	{
		FStringAssetReference testAssetRef = " /Game/UGameAssets/Assets/horizo​​n/flipbook/hero_down ";
		UPaperFlipbook* pObject = Cast<UPaperFlipbook>(testAssetRef.TryLoad());
	}
	{
		FStringAssetReference testAssetRef = " /Game/UGameAssets/Assets/horizo​​n/spriter/MyTexture ";
		UTexture2D* pObject = Cast<UTexture2D>(testAssetRef.TryLoad());
	}
}

MY_END_NAMESPACE