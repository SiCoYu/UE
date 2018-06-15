#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainChild : PlayerChild
{
	public PlayerMainChild()
	{
		this.mTypeId = "PlayerMainChild";
		this.mEntityType = EntityType.ePlayerMainChild;
		this.mMovement = new PlayerMainChildMovement(this);
		this.mAttack = new PlayerMainChildAttack(this);
		this.mEntityUniqueId = Ctx.msInstance.mPlayerMgr.genChildNewStrId();

		this.setLastMergedTime();

		//this.mPlayerMainChildAI = new PlayerMainChildAI(this);
		//(this.mParentPlayer as PlayerMain).addVehicle(this.mPlayerMainChildAI.getVehicle());
		//this.mPlayerMainChildAI.setVehicleList((this.mParentPlayer as PlayerMain).getNeighbors());
	}

	override public void initRender()
	{
		if (!this.isPrefabPathValid())
		{
			this.setPrefabPath("World/Model/PlayerMain.prefab");
		}

		if (null == this.mRender)
		{
			this.mRender = new PlayerMainChildRender(this);
		}

		this.mRender.init();
	}

	protected override void _onPreInit()
	{
		base._onPreInit();

		this.mMovement.init();
		this.mAttack.init();
		//this.mPlayerMainChildAI.init();
	}

	public override void onTick(float delta, TickMode tickMode)
	{
		base.onTick(delta, tickMode);

		//this.mPlayerMainChildAI.onTick(delta, tickMode);
	}

	public void postUpdate()
	{
		if(this.mRender.isValid())
		{
			this.setRenderPos(this.mRender.getPos());
		}
	}

	public override void onDestroy()
	{
		//(this.mParentPlayer as PlayerMain).removeVehicle(this.mPlayerMainChildAI.getVehicle());

		base.onDestroy();

		if (null != Ctx.msInstance.mGlobalDelegate)
		{
			Ctx.msInstance.mGlobalDelegate.mMainChildMassChangedDispatch.dispatchEvent(null);
		}
	}

	override public void onPutInPool()
	{
		base.onPutInPool();

		Ctx.msInstance.mGlobalDelegate.mMainChildMassChangedDispatch.dispatchEvent(null);
	}

	public override void dispose()
	{
		base.dispose();
	}

	public override void putInPool()
	{
		base.putInPool();
	}

	override public void setBeingState(BeingState state)
	{
		base.setBeingState(state);

		if(BeingState.eBSBirth == this.mBeingState)
		{
			this.mMoveSpeedFactor = 5;
		}
		else
		{
			this.mMoveSpeedFactor = 1;
		}
	}

	override public void setRenderPos(UnityEngine.Vector3 pos)
	{
		if (!UtilEngineWrap.isInFakePos(pos) && !UtilMath.isEqualVec3(this.mPos, pos))
		{
			this.mPos = pos;

			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRenderPos, BasicInfo is {0}, mPosX = {1}, mPosY = {2}, mPosZ = {3}", this.getBasicInfoStr(), this.mPos.x, this.mPos.y, this.mPos.z), LogTypeId.eLogBeingMove);
			}
		}
	}
};

MY_END_NAMESPACE