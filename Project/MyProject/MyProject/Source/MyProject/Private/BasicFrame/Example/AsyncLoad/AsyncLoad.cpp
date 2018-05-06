#include "MyProject.h"
#include "AsyncLoad.h"

UAsyncLoad::UAsyncLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UAsyncLoad::SimpleAsyncLoad()
{
	FStringAssetReference AssetToLoad;
	// UE 4.19.1 warning C4996: 'TSoftObjectPtr<ABaseItem>::ToStringReference': ToStringReference was renamed to ToSoftObjectPath Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//AssetToLoad = MyItem.ToStringReference();
	AssetToLoad = MyItem.ToSoftObjectPath();
	// UE 4.19.1 warning C4996: 'FStreamableManager::SimpleAsyncLoad': Call RequestAsyncLoad with bManageActiveHandle=true instead if you want the manager to keep the handle alive Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//this->AssetLoader.SimpleAsyncLoad(AssetToLoad);
	this->AssetLoader.RequestAsyncLoad(
		AssetToLoad, 
		FStreamableDelegate(), 
		FStreamableManager::DefaultAsyncLoadPriority,
		true);
}

void UAsyncLoad::RequestAsyncLoad()
{
	TArray<FStringAssetReference> AssetsToLoad;
	for (TAssetPtr<ABaseItem>& AssetPtr : MyItems) // C++11 ranged loop
	{
		// UE 4.19.1 warning C4996: 'TSoftObjectPtr<ABaseItem>::ToStringReference': ToStringReference was renamed to ToSoftObjectPath Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//AssetsToLoad.AddUnique(AssetPtr.ToStringReference());
		AssetsToLoad.AddUnique(AssetPtr.ToSoftObjectPath());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UAsyncLoad::MyFunctionToBeCalledAfterAssetsAreLoaded));
}

void UAsyncLoad::MyFunctionToBeCalledAfterAssetsAreLoaded()
{

}