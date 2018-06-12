#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AuxComponent : public GObject
{
protected:

public:
	AuxComponent();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE