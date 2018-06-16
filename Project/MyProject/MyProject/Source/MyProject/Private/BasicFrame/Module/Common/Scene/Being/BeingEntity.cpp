#include "MyProject.h"
#include "BeingEntity.h"
#include "BeingEntityMovement.h"
#include "UtilMath.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

BeingEntity::BeingEntity()
{
	this->mBeingState = BeingState::eBSIdle;
	this->mBeingSubState = BeingSubState::eBSSNone;

	this->mRotateSpeed = 10;
	this->mScaleSpeed = 0;
	
	this->mName = "";
	this->mMoveSpeedFactor = 1;
}

void BeingEntity::onDestroy()
{
	//if (nullptr != this->mHud)
	//{
	//	this->mHud.dispose();
	//	this->mHud = nullptr;
	//}

	if (nullptr != this->mMovement)
	{
		this->mMovement->dispose();
		this->mMovement = nullptr;
	}

	if (nullptr != this->mAttack)
	{
		this->mAttack.dispose();
		this->mAttack = nullptr;
	}

	Super::onDestroy();
}

void BeingEntity::onPutInPool()
{
	this->mBeingState = BeingState.eBSIdle;
	this->mBeingSubState = BeingSubState.eBSSNone;

	this->mRotateSpeed = 10;

	this->mName = "";
	this->mMoveSpeedFactor = 1;

	//if (nullptr != this->mHud)
	//{
	//	this->mHud.onPutInPool();
	//}

	if (nullptr != this->mMovement)
	{
		this->mMovement->onPutInPool();
	}

	if (nullptr != this->mAttack)
	{
		this->mAttack.onPutInPool();
	}

	Super::onPutInPool();
}

void BeingEntity::setMoveSpeed(float value)
{
	this->mMoveSpeed = value;
}

float BeingEntity::getMoveSpeed(bool isOrig = false)
{
	return this->mMoveSpeed;
}

void BeingEntity::setRotateSpeed(float value)
{
	this->mRotateSpeed = value;
}

float BeingEntity::getRotateSpeed()
{
	return this->mRotateSpeed;
}

void BeingEntity::setScaleSpeed(float value)
{
	this->mScaleSpeed = value;
}

float BeingEntity::getScaleSpeed()
{
	return this->mScaleSpeed;
}

void BeingEntity::setDestPos(FVector pos, bool immePos)
{
	if (immePos)
	{
		this->setPos(pos);
	}
	if (nullptr != mMovement)
	{
		((BeingEntityMovement*)this->mMovement)->setDestPos(pos);
	}
}

FVector BeingEntity::getDestPos()
{
	if (nullptr != this->mMovement)
	{
		return ((BeingEntityMovement*)this->mMovement)->getDestPos();
	}

	return UtilMath::ZeroVec3;
}

void BeingEntity::setDestRotateEulerAngle(FVector rotate, bool immeRotate)
{
	if (immeRotate)
	{
		this->setRotateEulerAngle(rotate);
	}
	if (nullptr != mMovement)
	{
		(mMovement as BeingEntityMovement).setDestRotateEulerAngle(rotate);
	}
}

void BeingEntity::setDestRotate(UnityEngine.Quaternion rotate, bool immeRotate)
{
	if (immeRotate)
	{
		this->setRotate(rotate);
	}
	if (nullptr != mMovement)
	{
		(mMovement as BeingEntityMovement).setDestRotate(rotate);
	}
}

void BeingEntity::setDestPosAndDestRotate(FVector targetPt, bool immePos, bool immeRotate)
{
	if (immePos)
	{
		this->setPos(targetPt);
	}

	UnityEngine.Quaternion retQuat = UtilMath.getRotateByStartAndEndPoint(this->getPos(), targetPt);
	if (immeRotate)
	{
		this->setRotateEulerAngle(retQuat.eulerAngles);
	}
	if (nullptr != mMovement)
	{
		(mMovement as BeingEntityMovement).setDestPos(targetPt);
	}
}

void BeingEntity::setDestScale(float scale, bool immeScale)
{
	if (immeScale)
	{
		this->setScale(new FVector(scale, scale, scale));
	}

	if (nullptr != mMovement)
	{
		(mMovement as BeingEntityMovement).setDestScale(scale);
	}
}

// 设置前向旋转
void BeingEntity::setForwardRotate(FVector rotate)
{
	if (nullptr != mMovement)
	{
		(mMovement as BeingEntityMovement).setForwardRotate(rotate);
	}
}

void BeingEntity::setName(std::string name)
{
	if (!string.IsNullOrEmpty(name))
	{
		this->mName = name;

		if (nullptr != this->mHud)
		{
			this->mHud.onNameChanged();
		}
	}
}

std::string BeingEntity::getName()
{
	return this->mName;
}

void BeingEntity::_onPreInit()
{
	// 基类初始化
	Super::_onPreInit();
	// 自动处理，例如添加到管理器
	this->autoHandle();
	// 初始化渲染器
	this->initRender();

	this->loadRenderRes();
}

void BeingEntity::_onPostInit()
{
	Super::_onPostInit();
}

void BeingEntity::loadRenderRes()
{
	if (nullptr != this->mRender)
	{
		this->mRender.load();
	}
}

void BeingEntity::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);
}

// Tick 第一阶段执行
void BeingEntity::_onPreTick(float delta, TickMode tickMode)
{
	Super::_onPreTick(delta, tickMode);
}

// Tick 第二阶段执行
void BeingEntity::_onPostTick(float delta, TickMode tickMode)
{
	if (nullptr != this->mMovement)
	{
		this->mMovement.onTick(delta, tickMode);
	}

	if (nullptr != this->mAttack)
	{
		this->mAttack.onTick(delta, tickMode);
	}
}

// 获取 Hud 场景中的位置
//virtual FVector getHudPos()
//{
//	this->mHudPos = this->mPos;

//	return this->mHudPos;
//}

void BeingEntity::setBeingState(BeingState state)
{
	if (this->mBeingState != state)
	{
		this->mBeingState = state;
	}
}

BeingState BeingEntity::getBeingState()
{
	return this->mBeingState;
}

void BeingEntity::setBeingSubState(BeingSubState subState)
{
	if (this->mBeingSubState != subState)
	{
		this->mBeingSubState = subState;
	}
}

BeingSubState BeingEntity::getBeingSubState()
{
	return this->mBeingSubState;
}

void BeingEntity::clearBeingSubState()
{
	this->mBeingSubState = BeingSubState.eBSSNone;
}

void BeingEntity::overlapToEnter(BeingEntity bBeingEntity, const FHitResult& SweepResult)
{
	this->mAttack.overlapToEnter(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToStay(BeingEntity bBeingEntity, const FHitResult& SweepResult)
{
	this->mAttack.overlapToStay(bBeingEntity, collisionInfo);
}

void BeingEntity::overlapToExit(BeingEntity bBeingEntity, const FHitResult& SweepResult)
{
	this->mAttack.overlapToExit(bBeingEntity, collisionInfo);
}

UnityEngine.Quaternion BeingEntity::getDestRotate()
{
	if (nullptr != this->mMovement)
	{
		return (this->mMovement as BeingEntityMovement).getDestRotate();
	}

	return UtilMath.UnitQuat;
}

// 预制目录是否有效
bool BeingEntity::isPrefabPathValid()
{
	return !string.IsNullOrEmpty(this->mPrefabPath);
}

void BeingEntity::setPrefabPath(std::string path)
{
	this->mPrefabPath = path;
}

std::string BeingEntity::getPrefabPath()
{
	return this->mPrefabPath;
}

// 关联到父节点
void BeingEntity::attachToParentNode(EntityRenderBase* render)
{

}

void BeingEntity::setMoveSpeedFactor(float value)
{
	this->mMoveSpeedFactor = value;
}

MY_END_NAMESPACE