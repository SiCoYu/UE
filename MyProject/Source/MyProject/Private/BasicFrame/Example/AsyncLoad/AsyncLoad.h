#pragma once

#include "MyProject.h"
#include "BaseItem.h"
#include "AsyncLoad.generated.h"

/**
 * @brief https://wiki.unrealengine.com/TAssetPtr_and_Asynchronous_Asset_Loading
 * @brief http://www.cnblogs.com/sevenyuan/p/5685361.html
 */
UCLASS(config=Game)
class UAsyncLoad : public UObject
{
	GENERATED_BODY()
	
	FStreamableManager AssetLoader;
	TAssetPtr<ABaseItem> MyItem;
	TArray< TAssetPtr<ABaseItem> > MyItems;

public:
	UAsyncLoad(const FObjectInitializer& ObjectInitializer);

	void SimpleAsyncLoad();
	void RequestAsyncLoad();
	void MyFunctionToBeCalledAfterAssetsAreLoaded();
};