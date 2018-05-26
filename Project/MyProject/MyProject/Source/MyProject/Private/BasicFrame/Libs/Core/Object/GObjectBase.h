#pragma once

#include "MClassMacros.h"
#include "MClassInfo.h"
#include "MMutex.h"
#include "MClassMacros.h"

class GObjectBase
{
	M_DECLARE_CLASS(GObjectBase)

public:
	GObjectBase();

protected:
	virtual ~GObjectBase();
};