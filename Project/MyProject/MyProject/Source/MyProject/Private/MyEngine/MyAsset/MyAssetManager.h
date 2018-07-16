#pragma once

#include "Engine/AssetManager.h"	 // UAssetManager
//#include "MyAssetManager.generated.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ��Դ�Ļ�������ʹ�ã��������ж����Դ
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
};

MY_END_NAMESPACE