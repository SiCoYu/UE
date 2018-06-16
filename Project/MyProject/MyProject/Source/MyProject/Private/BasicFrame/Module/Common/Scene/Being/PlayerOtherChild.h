#pragma once

#include "PlayerChild.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerOtherChild : public PlayerChild
{
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

public:
	PlayerOtherChild();

	virtual void initRender() override;
};

MY_END_NAMESPACE