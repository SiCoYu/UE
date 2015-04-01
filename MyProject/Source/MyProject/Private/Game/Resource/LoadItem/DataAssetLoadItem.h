#pragma once
#include "Engine/DataAsset.h"
#include "DataAssetLoadItem.generated.h"

UCLASS(config = Game)
class UDataAssetLoadItem : public UDataAsset
{
	GENERATED_BODY()

public:
	void loadFile(const FString& Filename);
};