#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObjectBase
{
	M_DECLARE_ROOT_CLASS(GObjectBase)

public:
	GObjectBase();

protected:
	virtual ~GObjectBase();
};

MY_END_NAMESPACE