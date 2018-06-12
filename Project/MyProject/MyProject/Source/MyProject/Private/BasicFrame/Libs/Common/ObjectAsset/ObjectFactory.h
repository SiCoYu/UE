#pragma once

#include "BuildFactoryBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject;

class ObjectFactory : public BuildFactoryBase
{
public:
	ObjectFactory()
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