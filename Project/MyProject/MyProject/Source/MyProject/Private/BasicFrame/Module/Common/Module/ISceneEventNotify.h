#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ISceneEventNotify : public GObject
{
public:
	virtual void onLevelLoaded()
	{

	}

	virtual void init()
	{

	}

	virtual void dispose()
	{

	}
};

MY_END_NAMESPACE