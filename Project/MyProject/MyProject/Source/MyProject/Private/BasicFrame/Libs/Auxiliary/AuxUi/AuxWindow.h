#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AuxWindow : public GObject
{
	M_DECLARE_CLASS(AuxWindow, GObject)

public:
	virtual void init();
	virtual void dispose();
};

MY_END_NAMESPACE