#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MYPROJECT_API AuxActor : public GObject
{
protected:

public:
	AuxActor();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE