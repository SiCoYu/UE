#pragma once

#include "GObject.h"
#include "BaseClassDef.h"

class GContainerObject : public GObject
{
	M_DECLARE_SUPER_KW(GObject)

public:
	GContainerObject();
};