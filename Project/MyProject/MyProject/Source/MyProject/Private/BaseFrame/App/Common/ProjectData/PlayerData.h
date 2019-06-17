#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 基本是主角自己的数据
 */
class PlayerData : public GObject
{
	M_DECLARE_CLASS(PlayerData, GObject)

public:
	PlayerData();

	void init();
	void dispose();
};

MY_END_NAMESPACE