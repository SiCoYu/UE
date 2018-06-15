#pragma once

#include "AuxComponent.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AuxWindow : public AuxComponent
{
	M_DECLARE_CLASS(AuxWindow, AuxComponent)

public:
	virtual void init();
	virtual void dispose();
};

MY_END_NAMESPACE