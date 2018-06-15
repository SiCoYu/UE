#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 场景中的玩家
 */
public class Player : BeingEntity
{
	public Player()
	{

	}

	override protected void _onPreInit()
	{
		base._onPreInit();
	}

	protected override void _onPostInit()
	{
		base._onPostInit();
	}

	override public void onDestroy()
	{
		base.onDestroy();
	}

	override public void onPutInPool()
	{
		base.onPutInPool();
	}

	override public void autoHandle()
	{
		base.autoHandle();
	}

	override public void initRender()
	{
		this.mRender = new PlayerRender(this);
		this.mRender.init();
	}
};

MY_END_NAMESPACE