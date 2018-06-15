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
	protected MList<Vehicle2D> mNeighbors;

	public SteerInfo mSteerInfo;

	public PlayerMain()
	{
		this.mTypeId = "PlayerMain";
		this.mEntityType = EntityType.ePlayerMain;
		this.mEntityUniqueId = Ctx.msInstance.mPlayerMgr.genNewStrId();
		this.mMovement = new PlayerMainMovement(this);
		this.mAttack = new PlayerMainAttack(this);

		//this.mMutilRigidCalcPolicy = new MutilRigidCalcPolicy();

		this.mNeighbors = new MList<Vehicle2D>();
		this.mNeighbors.setIsSpeedUpFind(true);
		this.mSteerInfo = new SteerInfo();
	}

	override public void initRender()
	{
		if (null == this.mRender)
		{
			this.mRender = new PlayerMainRender(this);
		}

		this.mRender.init();
		//this.mRender = null;        // 不需要渲染器
	}

	protected override void _onPreInit()
	{
		base._onPreInit();

		//this.hide();    // PlayerMain 不显示，仅仅记录数据

		this.mMovement.init();
		this.mAttack.init();

		//Ctx.msInstance.mGlobalDelegate.mMainChildMassChangedDispatch.addEventHandle(null, this.onChildMassChanged);
		//this.mMutilRigidCalcPolicy.init();
	}

	protected override void _onPostInit()
	{
		base._onPostInit();
	}

	override public void dispose()
	{
		//this.mMutilRigidCalcPolicy.dispose();
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

		//this.mMutilRigidCalcPolicy.onTick(delta, tickMode);
	}

	public void emitSnowBlock()
	{
		
	}

	override public void setName(string name)
	{
		base.setName(name);
	}

	public void onChildChanged()
	{
		
	}
	
	public void moveForwardByOrient(UnityEngine.Vector2 orient)
	{
		UnityEngine.Vector3 dir = UtilEngineWrap.convPosByMode(new UnityEngine.Vector3(orient.x, 0, orient.y));
		UnityEngine.Quaternion quad = UtilMath.getRotateByOrient(dir) * (this.mMovement as PlayerMainMovement).getForwardRotate();

		this.setDestRotateEulerAngle(quad.eulerAngles, true);
		(this.mMovement as PlayerMainMovement).moveForward();
	}

	// 摇杆按下，但是不移动
	public void onPressButNoMove()
	{
		if (BeingState.eBSMoveCenter != this.mBeingState)
		{
			
		}
	}

	public void stopMove()
	{
		(this.mMovement as PlayerMainMovement).stopMove();
	}

	//public bool isChildEnableRigidByThisId(uint thisId)
	//{
	//    PlayerMainChild child = this.mPlayerSplitMerge.mPlayerChildMgr.getEntityByThisId(thisId) as PlayerMainChild;
	//    return this.mMutilRigidCalcPolicy.isChildEnableRigidByThisId(child);
	//}

	public void addVehicle(Vehicle2D vehicle)
	{
		if (!this.mNeighbors.contains(vehicle))
		{
			this.mNeighbors.add(vehicle);
		}
	}

	public void removeVehicle(Vehicle2D vehicle)
	{
		if (this.mNeighbors.contains(vehicle))
		{
			this.mNeighbors.remove(vehicle);
		}
	}

	public MList<Vehicle2D> getNeighbors()
	{
		return this.mNeighbors;
	}

	public override void setRotate(Quaternion rotation)
	{
		base.setRotate(rotation);
	}

	public override void setPos(UnityEngine.Vector3 pos)
	{
		base.setPos(pos);
	}
};

MY_END_NAMESPACE