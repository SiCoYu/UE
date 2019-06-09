#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneNavigation : public GObject
{
	M_DECLARE_CLASS(SceneNavigation, GObject)

public:
	SceneNavigation();
	~SceneNavigation();
};

MY_END_NAMESPACE