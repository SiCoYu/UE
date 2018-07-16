#pragma once

#include "IAssetRegistry.h"		// IAssetRegistry
#include "UObject/NameTypes.h"	// FName
#include "Containers/Array.h"	// TArray
#include "Misc/AssetRegistryInterface.h"	// EAssetRegistryDependencyType
#include "GObject.h"
#include "PlatformDefine.h"

class FAssetRegistryModule;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ������Դ���ݣ������ȡ��Դ��������Դ·��
 * @url AssetRegistryModule.h
 * @url Engine\Source\Runtime\AssetRegistry\Private\AssetRegistry.h
 * @url Runtime\AssetRegistry\Public\IAssetRegistry.h
 */

class MyAssetRegistry : public GObject
{
public:
	MyAssetRegistry();
	~MyAssetRegistry();

	void init();
	void dispose();

	FAssetRegistryModule& getAssetRegistryModule();
	IAssetRegistry& getAssetRegistry()/* const*/;
	void _testA();
	void GetDependencies(FName PackageName, TArray<FName>& OutDependencies, EAssetRegistryDependencyType::Type InDependencyType = EAssetRegistryDependencyType::All);
};

MY_END_NAMESPACE