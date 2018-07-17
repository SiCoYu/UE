#pragma once

#include "Engine/AssetManager.h"		// UAssetManager
#include "MyNativeAssetManager.generated.h"


UCLASS()
class UMyNativeAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UMyNativeAssetManager();
	~UMyNativeAssetManager();
};