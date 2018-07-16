#include "MyProject.h"
#include "MyAssetRegistry.h"
#include "Containers/UnrealString.h"		// FString
#include "AssetData.h"	// FAssetData
#include "Engine/Texture2D.h"		// UTexture2D 
#include "AssetRegistryModule.h"	// FAssetRegistryModule

MY_BEGIN_NAMESPACE(MyNS)

MyAssetRegistry::MyAssetRegistry()
{

}

MyAssetRegistry::~MyAssetRegistry()
{
	
}

void MyAssetRegistry::init()
{
	
}

void MyAssetRegistry::dispose()
{

}

void MyAssetRegistry::_testA()
{
	// Engine\Plugins\2D\Paper2D\Source\Paper2DEditor\Private\PaperSpriteFactory.cpp
	// UObject* UPaperSpriteFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
	FString objectPath = TEXT("");

	// AssetRegistryModule.Get 返回 IAssetRegistry， Runtime\AssetRegistry\Public\IAssetRegistry.h ， UAssetRegistryImpl 接口 Engine\Source\Runtime\AssetRegistry\Private\AssetRegistry.h 
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(*objectPath);

	if (AssetData.IsValid())
	{
		if (UTexture2D* NormalMapTexture = Cast<UTexture2D>(AssetData.GetAsset()))
		{

		}
	}
}

MY_END_NAMESPACE