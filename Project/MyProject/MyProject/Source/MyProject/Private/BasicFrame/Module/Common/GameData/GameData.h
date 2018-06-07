#pragma once

#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

class GameData : public GObject
{
	M_DECLARE_CLASS(GameData, GObject)

public:
	GameData();

	void init();
	void dispose();
};

MY_END_NAMESPACE