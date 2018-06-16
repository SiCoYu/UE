#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 基本是主角自己的数据
 */
class ProjectData : public GObject
{
	M_DECLARE_CLASS(ProjectData, GObject)

public:
	ProjectData();

	void init();
	void dispose();
};

MY_END_NAMESPACE