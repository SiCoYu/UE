#pragma once

#include "BuildFactoryBase.h"
#include "TypeUniqueId.h"
#include "AssetUniqueId.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject;

class AssetFactory : public BuildFactoryBase
{
	M_DECLARE_CLASS(AssetFactory, BuildFactoryBase)

public:
	AssetFactory();

	void init();
	void dispose();
	GObject* createObject(
		TypeUniqueId typeUniqueId, 
		AssetUniqueId assetUniqueId
	);
};

MY_END_NAMESPACE