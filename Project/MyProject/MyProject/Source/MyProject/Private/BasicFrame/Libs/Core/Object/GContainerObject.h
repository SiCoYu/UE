#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

class GContainerObject : public GObject
{
	M_DECLARE_SUPER_KW(EventDispatch)

public:
	GContainerObject();
};