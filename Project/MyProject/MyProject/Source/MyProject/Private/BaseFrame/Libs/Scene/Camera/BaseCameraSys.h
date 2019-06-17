#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class BaseCameraSys : public GObject
{
public:
	BaseCameraSys();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE