#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

struct FLatentActionManager;

MY_BEGIN_NAMESPACE(MyNS)

class MyLatentActionManager : public GObject
{
protected:
	FLatentActionManager* mLatentActionManager;

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE