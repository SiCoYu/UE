#pragma once

#include "Engine/DataAsset.h"
#include "DataAssetLoadItem.generated.h"

/**
 * @brief 这个是按照 UE 的打包格式，但是目前还是不会使用，怎么自定义打包
 */
UCLASS(config = Game)
class UDataAssetLoadItem : public UDataAsset
{
	GENERATED_BODY()

public:
	void loadFile(const FString& Filename);
};