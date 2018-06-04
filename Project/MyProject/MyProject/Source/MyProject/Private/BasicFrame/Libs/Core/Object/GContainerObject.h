#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GContainerObject : public GObject
{
	M_DECLARE_CLASS(GContainerObject, GObject)

public:
	GContainerObject();
};

MY_END_NAMESPACE