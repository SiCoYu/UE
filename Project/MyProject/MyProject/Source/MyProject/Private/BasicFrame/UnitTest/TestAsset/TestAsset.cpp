#include "MyProject.h"
#include "TestAsset.h"
#include "MyAssetRegistry.h"
#include "Ctx.h"
#include "UObject/NameTypes.h"	// FName
#include "Containers/Array.h"	// TArray
#include "Misc/AssetRegistryInterface.h"	// EAssetRegistryDependencyType
#include "AssetData.h"	// FAssetData
#include "Engine/Texture2D.h"		// UTexture2D 

MY_BEGIN_NAMESPACE(MyNS)

void TestAsset::run()
{
	
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

MY_END_NAMESPACE