#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
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

#endif