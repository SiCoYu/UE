#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AuxActor : public GObject
{
protected:

public:
	AuxActor();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE