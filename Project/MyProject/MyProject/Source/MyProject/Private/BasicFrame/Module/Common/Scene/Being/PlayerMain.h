#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 主角
 */
public class PlayerMain : Player
{
	public PlayerMain()
	{
		this.mMovement = new PlayerMainMovement(this);
		this.mAttack = new PlayerMainAttack(this);
	}

	override public void initRender()
	{
		if (null == this.mRender)
		{
			this.mRender = new PlayerMainRender(this);
		}

		this.mRender.init();
	}

	protected override void _onPreInit()
	{
		base._onPreInit();

		this.mMovement.init();
		this.mAttack.init();
	}

	protected override void _onPostInit()
	{
		base._onPostInit();
	}

	override public void dispose()
	{
		if (null != Ctx.msInstance.mPlayerMgr)
		{
			Ctx.msInstance.mPlayerMgr.removeHero();
		}

		base.dispose();
	}

	override public void putInPool()
	{
		Ctx.msInstance.mPlayerMgr.removeHero();

		base.putInPool();
	}

	public override void onPutInPool()
	{
		base.onPutInPool();
	}

	override public void autoHandle()
	{
		base.autoHandle();

		Ctx.msInstance.mPlayerMgr.addHero(this);
	}

	protected override void _onExecTick(float delta, TickMode tickMode)
	{
		base._onExecTick(delta, tickMode);
	}

	protected override void _onPreTick(float delta, TickMode tickMode)
	{
		base._onPreTick(delta, tickMode);
	}

	protected override void _onPostTick(float delta, TickMode tickMode)
	{
		base._onPostTick(delta, tickMode);
	}
};

MY_END_NAMESPACE