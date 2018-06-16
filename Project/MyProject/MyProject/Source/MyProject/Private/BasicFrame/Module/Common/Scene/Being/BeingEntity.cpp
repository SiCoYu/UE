#include "MyProject.h"
#include "BeingEntity.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

BeingEntity::BeingEntity()
{
	this.mBeingState = BeingState::eBSIdle;
	this.mBeingSubState = BeingSubState::eBSSNone;

	this.mRotateSpeed = 10;
	this.mScaleSpeed = 0;
	
	this.mName = "";
	this.mMoveSpeedFactor = 1;
}

void BeingEntity::onDestroy()
{
	//if (null != this.mHud)
	//{
	//	this.mHud.dispose();
	//	this.mHud = null;
	//}

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

void BeingEntity::onPutInPool()
{
	this.mBeingState = BeingState.eBSIdle;
	this.mBeingSubState = BeingSubState.eBSSNone;

	this.mRotateSpeed = 10;

	this.mName = "";
	this.mMoveSpeedFactor = 1;

	//if (null != this.mHud)
	//{
	//	this.mHud.onPutInPool();
	//}

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

void BeingEntity::setMoveSpeed(float value)
{
	this.mMoveSpeed = value;
}

float BeingEntity::getMoveSpeed(bool isOrig = false)
{
	return this.mMoveSpeed;
}

void BeingEntity::setRotateSpeed(float value)
{
	this.mRotateSpeed = value;
}

float BeingEntity::getRotateSpeed()
{
	return this.mRotateSpeed;
}

void BeingEntity::setScaleSpeed(float value)
{
	this.mScaleSpeed = value;
}

float BeingEntity::getScaleSpeed()
{
	return this.mScaleSpeed;
}

void BeingEntity::setDestPos(UnityEngine.Vector3 pos, bool immePos)
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

UnityEngine.Vector3 BeingEntity::getDestPos()
{
	if (null != this.mMovement)
	{
		return (this.mMovement as BeingEntityMovement).getDestPos();
	}

	return UtilMath.ZeroVec3;
}

void BeingEntity::setDestRotateEulerAngle(UnityEngine.Vector3 rotate, bool immeRotate)
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

void BeingEntity::setDestRotate(UnityEngine.Quaternion rotate, bool immeRotate)
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

void BeingEntity::setDestPosAndDestRotate(UnityEngine.Vector3 targetPt, bool immePos, bool immeRotate)
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

void BeingEntity::setDestScale(float scale, bool immeScale)
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
void BeingEntity::setForwardRotate(UnityEngine.Vector3 rotate)
{
	if (null != mMovement)
	{
		(mMovement as BeingEntityMovement).setForwardRotate(rotate);
	}
}

void BeingEntity::setName(std::string name)
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

std::string BeingEntity::getName()
{
	return this.mName;
}

void BeingEntity::_onPreInit()
{
	// 基类初始化
	base._onPreInit();
	// 自动处理，例如添加到管理器
	this.autoHandle();
	// 初始化渲染器
	this.initRender();

	this.loadRenderRes();
}

void BeingEntity::_onPostInit()
{
	base._onPostInit();
}

void BeingEntity::loadRenderRes()
{
	if (null != this.mRender)
	{
		this.mRender.load();
	}
}

void BeingEntity::onTick(float delta, TickMode tickMode)
{
	base.onTick(delta, tickMode);
}

// Tick 第一阶段执行
void BeingEntity::_onPreTick(float delta, TickMode tickMode)
{
	base._onPreTick(delta, tickMode);
}

// Tick 第二阶段执行
void BeingEntity::_onPostTick(float delta, TickMode tickMode)
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
//virtual UnityEngine.Vector3 getHudPos()
//{
//	this.mHudPos = this.mPos;

//	return this.mHudPos;
//}

void BeingEntity::setBeingState(BeingState state)
{
	if (this.mBeingState != state)
	{
		this.mBeingState = state;
	}
}

BeingState BeingEntity::getBeingState()
{
	return this.mBeingState;
}

void BeingEntity::setBeingSubState(BeingSubState subState)
{
	if (this.mBeingSubState != subState)
	{
		this.mBeingSubState = subState;
	}
}

BeingSubState BeingEntity::getBeingSubState()
{
	return this.mBeingSubState;
}

void BeingEntity::clearBeingSubState()
{
	this.mBeingSubState = BeingSubState.eBSSNone;
}

void BeingEntity::overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
{
	this.mAttack.overlapToEnter(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
{
	this.mAttack.overlapToStay(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
{
	this.mAttack.overlapToExit(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
{
	this.mAttack.overlapToEnter2D(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
{
	this.mAttack.overlapToStay2D(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
{
	this.mAttack.overlapToExit2D(bBeingEntity, collisionInfo);
}

UnityEngine.Quaternion BeingEntity::getDestRotate()
{
	if (null != this.mMovement)
	{
		return (this.mMovement as BeingEntityMovement).getDestRotate();
	}

	return UtilMath.UnitQuat;
}

// 预制目录是否有效
bool BeingEntity::isPrefabPathValid()
{
	return !string.IsNullOrEmpty(this.mPrefabPath);
}

void BeingEntity::setPrefabPath(std::string path)
{
	this.mPrefabPath = path;
}

std::string BeingEntity::getPrefabPath()
{
	return this.mPrefabPath;
}

// 关联到父节点
void BeingEntity::attachToParentNode(EntityRenderBase* render)
{

}

void BeingEntity::setMoveSpeedFactor(float value)
{
	this.mMoveSpeedFactor = value;
}

MY_END_NAMESPACE