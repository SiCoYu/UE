#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerOtherMovement : BeingEntityMovement
{
	public PlayerOtherMovement(SceneEntityBase entity)
		: base(entity)
	{

	}

	override public void onTick(float delta, TickMode tickMode)
	{
		base.onTick(delta, tickMode);
	}
};

MY_END_NAMESPACE