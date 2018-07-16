#pragma once

#include "UObject/PrimaryAssetId.h"		// FPrimaryAssetId
#include "Engine/AssetManager.h"		// UAssetManager
#include "AssetData.h"			// FAssetData
//#include "MyAssetManager.generated.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 资源的基本管理使用，例如加载卸载资源
 * @src Engine\Source\Runtime\Engine\Classes\Engine\AssetManager.h
 * @src Engine\Source\Runtime\Engine\Private\AssetManager.cpp
 * @ref Engine\Plugins\Editor\AssetManagerEditor\Source\AssetManagerEditor\Private\AssetManagerEditorModule.cpp
 */

//UCLASS()
//class UMyAssetManager : public UAssetManager
class MyAssetManager
{
	//GENERATED_BODY()

public:
	//UMyAssetManager();
	//~UMyAssetManager();
	MyAssetManager();

	void init();
	void dispose();

	FPrimaryAssetId getPrimaryAssetIdFromAssetData(const FAssetData& AssetData)
};

MY_END_NAMESPACE