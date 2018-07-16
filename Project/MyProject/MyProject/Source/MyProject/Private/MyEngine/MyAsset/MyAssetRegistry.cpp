#include "MyProject.h"
#include "MyAssetRegistry.h"
#include "Containers/UnrealString.h"		// FString
#include "AssetData.h"	// FAssetData
#include "Engine/Texture2D.h"		// UTexture2D 
#include "AssetRegistryModule.h"	// FAssetRegistryModule
#include "IAssetRegistry.h"		// IAssetRegistry

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

FAssetRegistryModule& MyAssetRegistry::getAssetRegistryModule()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	return AssetRegistryModule;
}

IAssetRegistry& MyAssetRegistry::getAssetRegistry()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	return AssetRegistry;
}

FAssetData MyAssetRegistry::GetAssetByObjectPath(const FName ObjectPath, bool bIncludeOnlyOnDiskAssets)
{
	// Engine\Plugins\2D\Paper2D\Source\Paper2DEditor\Private\PaperSpriteFactory.cpp
	// UObject* UPaperSpriteFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
	// AssetRegistryModule.Get 返回 IAssetRegistry， Runtime\AssetRegistry\Public\IAssetRegistry.h ， UAssetRegistryImpl 接口 Engine\Source\Runtime\AssetRegistry\Private\AssetRegistry.h 
	FAssetRegistryModule& AssetRegistryModule = this->getAssetRegistryModule();
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(ObjectPath);
	return AssetData;
}

void MyAssetRegistry::GetDependencies(FName PackageName, TArray<FName>& OutDependencies, EAssetRegistryDependencyType::Type InDependencyType)
{
	FAssetRegistryModule& AssetRegistryModule = this->getAssetRegistryModule();
	AssetRegistryModule.GetDependencies(PackageName, OutDependencies, InDependencyType);
}

MY_END_NAMESPACE