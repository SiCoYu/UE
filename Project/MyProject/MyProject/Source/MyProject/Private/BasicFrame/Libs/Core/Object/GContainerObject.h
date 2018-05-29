#pragma once

#include "GObject.h"
#include "BaseClassDef.h"

MY_BEGIN_NAMESPACE(MyNS)

class GContainerObject : public GObject
{
	M_DECLARE_SUPER_KW(GObject)

public:
	GContainerObject();
};

MY_END_NAMESPACE