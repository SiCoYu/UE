#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

class ProjectData : public GObject
{
	M_DECLARE_CLASS(ProjectData, GObject)

public:
	ProjectData();

	void init();
	void dispose();
};

MY_END_NAMESPACE