#pragma once

#include "BuildFactoryBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject;

class AssetFactory : public BuildFactoryBase
{
public:
	AssetFactory()
	{

	}

	void init()
	{
		
	}

	void dispose()
	{
		
	}

	GObject* createObject(typeUniqueId, assetUniqueId)
	{
		var ret = null;
		var tmpl = null;

		return ret;
	}
};

MY_END_NAMESPACE