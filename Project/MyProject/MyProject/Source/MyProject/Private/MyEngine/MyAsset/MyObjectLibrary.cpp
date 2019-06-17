#include "MyProject.h"
#include "MyAssetManager.h"
#include "MyNativeAssetManager.h"

MY_BEGIN_NAMESPACE(MyNS)

MyAssetManager::MyAssetManager()
{
	
}

//UMyAssetManager::~UMyAssetManager()
//{
//	
//}

void MyAssetManager::init()
{
	if (UAssetManager::IsValid())
	{
		UAssetManager& AssetManager = UAssetManager::Get();
		TArray<FPrimaryAssetTypeInfo> TypeInfos;
		AssetManager.GetPrimaryAssetTypeInfoList(TypeInfos);
	}
}

void MyAssetManager::dispose()
{

}

FPrimaryAssetId MyAssetManager::getPrimaryAssetIdFromAssetData(const FAssetData& AssetData)
{
	// Engine\Plugins\Editor\AssetManagerEditor\Source\AssetManagerEditor\Private\AssetManagerEditorModule.cpp
	// TSharedRef<SWidget> IAssetManagerEditorModule::MakePrimaryAssetIdSelector(FOnGetPrimaryAssetDisplayText OnGetDisplayText, FOnSetPrimaryAssetId OnSetId, bool bAllowClear, TArray<FPrimaryAssetType> AllowedTypes)

	UAssetManager& Manager = UAssetManager::Get();
	//UMyNativeAssetManager& Manager = UMyNativeAssetManager::Get();

	FPrimaryAssetId AssetId;

	if (AssetData.IsValid())
	{
		AssetId = Manager.GetPrimaryAssetIdForData(AssetData);
		ensure(AssetId.IsValid());
	}

	return AssetId;
}

MY_END_NAMESPACE