#pragma once
#include "Engine/DataAsset.h"
#include "BinaryLoadItem.generated.h"

UCLASS(config = Game)
class UBinaryLoadItem : public UDataAsset
{
	GENERATED_BODY()

public:
	void loadFile(const FString& Filename);
};