#pragma once

#include "MyProject.h"
#include "ObjectLibraryLoad.generated.h"

/**
 * @brief https://wiki.unrealengine.com/TAssetPtr_and_Asynchronous_Asset_Loading
 * @brief http://www.cnblogs.com/sevenyuan/p/5685361.html
 */
UCLASS(config=Game)
class UObjectLibraryLoad : public UObject
{
	GENERATED_BODY()

	UObjectLibrary* ObjectLibrary;

public:
	UObjectLibraryLoad(const FObjectInitializer& ObjectInitializer);

	void LoadAssetDataFromPath();
	void GetAssetDataFromPath(Class* BaseClass, bool bFullyLoad);
};