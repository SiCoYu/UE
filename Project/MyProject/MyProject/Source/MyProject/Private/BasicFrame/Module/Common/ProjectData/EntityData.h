#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 一个场景的数据，与主角基本没什么关系
 */
class EntityData : public GObject
{
	M_DECLARE_CLASS(EntityData, GObject)

public:
	EntityData();

	void init();
	void dispose();
};

MY_END_NAMESPACE