#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 生物 Entity，有感知，可以交互的
 */
class BeingEntity : public SceneEntityBase
{
	protected float mMoveSpeed;     // 移动速度
	protected float mRotateSpeed;   // 旋转速度
	protected float mScaleSpeed;    // 缩放速度

	protected float mMoveSpeedFactor;   // 移动速度因子
	
	public SceneEntityMovement mMovement;    // 移动组件
	public BeingEntityAttack mAttack;
	//protected HudItemBase mHud;     // HUD

	protected string mName;         // 名字
	public BeingAnimatorControl mAnimatorControl;
	protected string mPrefabPath;   // 预制的目录

	//protected UnityEngine.Vector3 mHudPos;

	public BeingEntity()
	{
		this.mBeingState = BeingState.eBSIdle;
		this.mBeingSubState = BeingSubState.eBSSNone;

		this.mRotateSpeed = 10;
		this.mScaleSpeed = 0;
		
		this.mName = "";
		this.mMoveSpeedFactor = 1;
	}

	public override void onDestroy()
	{
		if (null != this.mHud)
		{
			this.mHud.dispose();
			this.mHud = null;
		}

		if (null != this.mMovement)
		{
			this.mMovement.dispose();
			this.mMovement = null;
		}

		if (null != this.mAttack)
		{
			this.mAttack.dispose();
			this.mAttack = null;
		}

		base.onDestroy();
	}

	override public void onPutInPool()
	{
		this.mBeingState = BeingState.eBSIdle;
		this.mBeingSubState = BeingSubState.eBSSNone;

		this.mRotateSpeed = 10;

		this.mName = "";
		this.mMoveSpeedFactor = 1;
		this.mIsFreezeXZ = false;
		this.mTexPath = "";

		if (null != this.mHud)
		{
			this.mHud.onPutInPool();
		}

		if (null != this.mMovement)
		{
			this.mMovement.onPutInPool();
		}

		if (null != this.mAttack)
		{
			this.mAttack.onPutInPool();
		}

		base.onPutInPool();
	}

	virtual public void setMoveSpeed(float value)
	{
		this.mMoveSpeed = value;

		if (MacroDef.ENABLE_LOG)
		{
			Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setMoveSpeed, BasicInfo is = {0}, MoveSpeed = {1}", this.getBasicInfoStr(), this.mMoveSpeed), LogTypeId.eLogBeingMove);
		}
	}

	public float getMoveSpeed(bool isOrig = false)
	{
		return this.mMoveSpeed;
	}

	public void setRotateSpeed(float value)
	{
		this.mRotateSpeed = value;
	}

	public float getRotateSpeed()
	{
		return this.mRotateSpeed;
	}

	public void setScaleSpeed(float value)
	{
		this.mScaleSpeed = value;
	}

	public float getScaleSpeed()
	{
		return this.mScaleSpeed;
	}

	virtual public void setDestPos(UnityEngine.Vector3 pos, bool immePos)
	{
		if (immePos)
		{
			this.setPos(pos);
		}
		if (null != mMovement)
		{
			(mMovement as BeingEntityMovement).setDestPos(pos);
		}
	}

	public UnityEngine.Vector3 getDestPos()
	{
		if (null != this.mMovement)
		{
			return (this.mMovement as BeingEntityMovement).getDestPos();
		}

		return UtilMath.ZeroVec3;
	}

	public void setDestRotateEulerAngle(UnityEngine.Vector3 rotate, bool immeRotate)
	{
		if (immeRotate)
		{
			this.setRotateEulerAngle(rotate);
		}
		if (null != mMovement)
		{
			(mMovement as BeingEntityMovement).setDestRotateEulerAngle(rotate);
		}
	}

	public void setDestRotate(UnityEngine.Quaternion rotate, bool immeRotate)
	{
		if (immeRotate)
		{
			this.setRotate(rotate);
		}
		if (null != mMovement)
		{
			(mMovement as BeingEntityMovement).setDestRotate(rotate);
		}
	}
	
	public void setDestPosAndDestRotate(UnityEngine.Vector3 targetPt, bool immePos, bool immeRotate)
	{
		if (immePos)
		{
			this.setPos(targetPt);
		}

		UnityEngine.Quaternion retQuat = UtilMath.getRotateByStartAndEndPoint(this.getPos(), targetPt);
		if (immeRotate)
		{
			this.setRotateEulerAngle(retQuat.eulerAngles);
		}
		if (null != mMovement)
		{
			(mMovement as BeingEntityMovement).setDestPos(targetPt);
		}
	}

	public void setDestScale(float scale, bool immeScale)
	{
		if (immeScale)
		{
			this.setScale(new UnityEngine.Vector3(scale, scale, scale));
		}

		if (null != mMovement)
		{
			(mMovement as BeingEntityMovement).setDestScale(scale);
		}
	}

	// 设置前向旋转
	public void setForwardRotate(UnityEngine.Vector3 rotate)
	{
		if (null != mMovement)
		{
			(mMovement as BeingEntityMovement).setForwardRotate(rotate);
		}
	}

	virtual public void setName(string name)
	{
		if (!string.IsNullOrEmpty(name))
		{
			this.mName = name;

			if (null != this.mHud)
			{
				this.mHud.onNameChanged();
			}
		}
	}

	public string getName()
	{
		return this.mName;
	}

	override protected void _onPreInit()
	{
		// 基类初始化
		base._onPreInit();
		// 自动处理，例如添加到管理器
		this.autoHandle();
		// 初始化渲染器
		this.initRender();

		this.loadRenderRes();
	}

	protected override void _onPostInit()
	{
		base._onPostInit();
	}

	override public void loadRenderRes()
	{
		if (null != this.mRender)
		{
			this.mRender.load();
		}
	}

	override public void onTick(float delta, TickMode tickMode)
	{
		base.onTick(delta, tickMode);
	}

	// Tick 第一阶段执行
	override protected void _onPreTick(float delta, TickMode tickMode)
	{
		base._onPreTick(delta, tickMode);
	}

	// Tick 第二阶段执行
	override protected void _onPostTick(float delta, TickMode tickMode)
	{
		if (null != this.mMovement)
		{
			this.mMovement.onTick(delta, tickMode);
		}

		if (null != this.mAttack)
		{
			this.mAttack.onTick(delta, tickMode);
		}
	}

	// 获取 Hud 场景中的位置
	virtual public UnityEngine.Vector3 getHudPos()
	{
		this.mHudPos = this.mPos;

		return this.mHudPos;
	}

	virtual public void setBeingState(BeingState state)
	{
		if (this.mBeingState != state)
		{
			this.mBeingState = state;

			if (null != this.mAnimFSM)
			{
				this.mAnimFSM.MoveToState(AnimStateId.getStateIdByBeingState(this.mBeingState));
			}
		}
	}

	public BeingState getBeingState()
	{
		return this.mBeingState;
	}

	public void setBeingSubState(BeingSubState subState)
	{
		if (this.mBeingSubState != subState)
		{
			this.mBeingSubState = subState;
		}
	}

	public BeingSubState getBeingSubState()
	{
		return this.mBeingSubState;
	}

	public void clearBeingSubState()
	{
		this.mBeingSubState = BeingSubState.eBSSNone;
	}

	public void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		this.mAttack.overlapToEnter(bBeingEntity, collisionInfo);
	}

	public void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		this.mAttack.overlapToStay(bBeingEntity, collisionInfo);
	}

	public void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		this.mAttack.overlapToExit(bBeingEntity, collisionInfo);
	}

	public void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		this.mAttack.overlapToEnter2D(bBeingEntity, collisionInfo);
	}

	public void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		this.mAttack.overlapToStay2D(bBeingEntity, collisionInfo);
	}

	public void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		this.mAttack.overlapToExit2D(bBeingEntity, collisionInfo);
	}

	public UnityEngine.Quaternion getDestRotate()
	{
		if (null != this.mMovement)
		{
			return (this.mMovement as BeingEntityMovement).getDestRotate();
		}

		return UtilMath.UnitQuat;
	}

	// 预制目录是否有效
	public bool isPrefabPathValid()
	{
		return !string.IsNullOrEmpty(this.mPrefabPath);
	}

	public void setPrefabPath(string path)
	{
		this.mPrefabPath = path;
	}

	public string getPrefabPath()
	{
		return this.mPrefabPath;
	}
	
	// 关联到父节点
	virtual public void attachToParentNode(EntityRenderBase render)
	{

	}

	public void setMoveSpeedFactor(float value)
	{
		this.mMoveSpeedFactor = value;
	}
};

MY_END_NAMESPACE