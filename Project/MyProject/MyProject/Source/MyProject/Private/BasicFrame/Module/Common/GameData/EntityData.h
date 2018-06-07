#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

class EntityData : public GObject
{
	M_DECLARE_CLASS(EntityData, GObject)
};

MY_END_NAMESPACE