#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class BuildFactoryBase : public GObject
{
public:
	BuildFactoryBase()
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
		return ret;
	}
};

MY_END_NAMESPACE