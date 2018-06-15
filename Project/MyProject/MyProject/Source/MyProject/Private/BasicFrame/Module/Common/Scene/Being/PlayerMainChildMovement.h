#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainChildMovement : PlayerChildMovement
{
	public PlayerMainChildMovement(SceneEntityBase entity)
		: base(entity)
	{
		
	}

	override public void init()
	{
		base.init();
	}

	override public void dispose()
	{
		base.dispose();
	}

	public override void onPutInPool()
	{
		base.onPutInPool();
	}

	override public void onTick(float delta, TickMode tickMode)
	{
		base.onTick(delta, tickMode);
	}
};

MY_END_NAMESPACE