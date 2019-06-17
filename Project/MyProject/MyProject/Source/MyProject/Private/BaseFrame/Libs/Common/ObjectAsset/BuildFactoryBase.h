#pragma once

#include "GObject.h"
#include "TypeUniqueId.h"
#include "AssetUniqueId.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject;

class BuildFactoryBase : public GObject
{
	M_DECLARE_CLASS(BuildFactoryBase, GObject)

public:
	BuildFactoryBase();

	void init();
	void dispose();
	GObject* createObject(
		TypeUniqueId typeUniqueId, 
		AssetUniqueId assetUniqueId
	);
};

MY_END_NAMESPACE