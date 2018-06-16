#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief һ�����������ݣ������ǻ���ûʲô��ϵ
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