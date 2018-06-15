#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainMovement : PlayerMovement
{
	protected UnityEngine.Quaternion mForwardRotate;     // 记录当前的前向
	protected UnityEngine.Quaternion mRotate;

	public PlayerMainMovement(SceneEntityBase entity)
		: base(entity)
	{
		this.mForwardRotate = UtilMath.UnitQuat;
		this.mRotate = UtilMath.UnitQuat;
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

	public UnityEngine.Quaternion getForwardRotate()
	{
		return mForwardRotate;
	}

	override public void setForwardRotate(UnityEngine.Vector3 rotate)
	{
		mForwardRotate = UnityEngine.Quaternion.Euler(rotate);
	}
};

MY_END_NAMESPACE