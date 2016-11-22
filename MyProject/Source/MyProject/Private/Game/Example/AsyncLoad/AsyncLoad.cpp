#include "MyProject.h"
#include "AsyncLoad.h"

UAsyncLoad::UAsyncLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UAsyncLoad::SimpleAsyncLoad()
{
	FStringAssetReference AssetToLoad;
	this->AssetToLoad = MyItem.ToStringReference();
	this->AssetLoader.SimpleAsyncLoad(AssetToLoad);
}

void UAsyncLoad::RequestAsyncLoad()
{
	TArray<FStringAssetReference> AssetsToLoad;
	for (TAssetPtr<ABaseItem>& AssetPtr : MyItems) // C++11 ranged loop
	{
		AssetsToLoad.AddUnique(AssetPtr.ToStringReference());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &MyClass::MyFunctionToBeCalledAfterAssetsAreLoaded));
}

void UAsyncLoad::MyFunctionToBeCalledAfterAssetsAreLoaded()
{

}