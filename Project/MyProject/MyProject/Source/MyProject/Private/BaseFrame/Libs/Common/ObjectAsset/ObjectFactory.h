#pragma once

#include "BuildFactoryBase.h"
#include "TypeUniqueId.h"
#include "AssetUniqueId.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject;

class ObjectFactory : public BuildFactoryBase
{
	M_DECLARE_CLASS(ObjectFactory, BuildFactoryBase)

public:
	ObjectFactory();

	void init();
	void dispose();
	GObject* createObject(
		TypeUniqueId typeUniqueId,
		AssetUniqueId assetUniqueId
	);
};

MY_END_NAMESPACE