#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 操作资源数据，例如获取资源依赖，资源路径
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

	void _testA();
};

MY_END_NAMESPACE