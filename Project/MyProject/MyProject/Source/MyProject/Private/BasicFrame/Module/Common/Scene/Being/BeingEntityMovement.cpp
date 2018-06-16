#include "MyProject.h"
#include "BeingEntityMovement.h"
#include "SceneEntityBase.h"
#include "BeingEntity.h"
#include "MWrapQuaternion.h"
#include "UtilMath.h"
#include "Ctx.h"
#include "SystemTimeData.h"
#include "MacroDef.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(BeingEntityMovement, SceneEntityMovement)

BeingEntityMovement::BeingEntityMovement(SceneEntityBase* entity)
	: Super(entity), 
	mDestRotate(0, 0, 0, 1)
{
	this->mIsMoveToDest = false;
	this->mIsRotateToDest = false;
	this->mIsScaleToDest = false;
}

void BeingEntityMovement::dispose()
{
	Super::dispose();
}

void BeingEntityMovement::onPutInPool()
{
	this->mIsMoveToDest = false;
	this->mIsRotateToDest = false;
	this->mIsScaleToDest = false;

	this->mLastPos = UtilMath::ZeroVec3;
	this->mLastRotate = UtilMath::UnitQuat;

	this->mDestPos = UtilMath::ZeroVec3;
	this->mDestRotate.setRotation(UtilMath::UnitQuat);
	this->mDestScale = UtilMath::ZeroVec3;
	this->mDestRotate.clear();

	Super::onPutInPool();
}

bool BeingEntityMovement::isMoveToDest()
{
	return this->mIsMoveToDest;
}

void BeingEntityMovement::setIsMoveToDest(bool isMove)
{
	if (this->mIsMoveToDest != isMove)
	{
		this->mIsMoveToDest = isMove;
	}
}

bool BeingEntityMovement::isRotateToDest()
{
	return this->mIsRotateToDest;
}

void BeingEntityMovement::setRotateToDest(bool isRotate)
{
	if (this->mIsRotateToDest != isRotate)
	{
		this->mIsRotateToDest = isRotate;
	}
}

void BeingEntityMovement::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);

	if (this->mIsRotateToDest)
	{
		this->rotateToDest(delta);
	}

	if (this->mIsScaleToDest)
	{
		this->scaleToDest(delta);
	}

	if (this->mIsMoveToDest)
	{
		// 设置前向方向移动
		this->moveForwardToDest(delta);
	}
}

// 局部空间移动位置
void BeingEntityMovement::addActorLocalOffset(FVector DeltaLocation)
{
	FVector localOffset = this->mEntity->getRotate() * DeltaLocation;
	this->mEntity->setPos(this->mEntity->getPos() + localOffset);
}

// 向目的前向移动
void BeingEntityMovement::addActorLocalDestOffset(FVector DeltaLocation)
{
	FVector localOffset = this->mDestRotate.getRotate() * DeltaLocation;
	this->mEntity->setPos(this->mEntity->getPos() + localOffset);
}

// 向目的前向移动
void BeingEntityMovement::addActorLocalDestOffsetNoOrient(FVector DeltaLocation)
{
	FVector localOffset = DeltaLocation;
	this->mEntity->setPos(this->mEntity->getPos() + localOffset);
}

// 局部空间旋转
void BeingEntityMovement::addLocalRotation(FVector DeltaRotation)
{
	this->mEntity->setRotate(this->mEntity->getRotate() * UtilMath::convQuatFromEuler(DeltaRotation));
}

// 向前移动
void BeingEntityMovement::moveForward()
{
	if (BeingState::eBSWalk != ((BeingEntity*)this->mEntity)->getBeingState())
	{
		((BeingEntity*)this->mEntity)->setBeingState(BeingState::eBSWalk);
		this->setIsMoveToDest(true);
	}
}

// 向左旋转
void BeingEntityMovement::rotateLeft()
{
	float delta = GSystemTimeData->getFixedTimestep();

	FVector deltaRotation(0.0f, ((BeingEntity*)this->mEntity)->getRotateSpeed() * delta, 0.0f);
	this->addLocalRotation(deltaRotation);
}

// 向右旋转
void BeingEntityMovement::rotateRight()
{
	float delta = GSystemTimeData->getFixedTimestep();

	FVector deltaRotation(0.0f, -((BeingEntity*)this->mEntity)->getRotateSpeed() * delta, 0.0f);
	this->addLocalRotation(deltaRotation);
}

// 停止移动
void BeingEntityMovement::stopMove()
{
	
}

void BeingEntityMovement::stopRotate()
{
	this->setRotateToDest(false);
}

// 控制向前移动
void BeingEntityMovement::moveForwardToDest(float delta)
{
	FVector localMove(0.0f, 0.0f, ((BeingEntity*)this->mEntity)->getMoveSpeed() * delta);

	this->addActorLocalOffset(localMove);
}

// 自动寻路移动
void BeingEntityMovement::moveToDest(float delta)
{
	float dist = 0.0f;

	dist = FVector::Distance(FVector(this->mDestPos.X, 0.0f, this->mDestPos.Z),
			FVector(this->mEntity->getPos().X, 0.0f, this->mEntity->getPos().Z));

	float deltaSpeed = ((BeingEntity*)this->mEntity)->getMoveSpeed() * delta;

	if (dist > deltaSpeed)
	{
		FVector localMove(0.0f, 0.0f, ((BeingEntity*)this->mEntity)->getMoveSpeed() * delta);
		this->addActorLocalDestOffset(localMove);
	}
	else
	{
		this->mEntity->setPos(this->mDestPos);
		this->onArriveDestPos();
	}
}

// 移动到目标点，不用判断方向
void BeingEntityMovement::moveToDestNoOrient(float delta)
{
	//FVector normal = mDestPos - mEntity.getPos();
	//normal.Normalize();

	//float dist = 0.0f;
	//if (MacroDef.XZ_MODE)
	//{
	//	dist = FVector.Distance(new FVector(mDestPos.x, 0f, mDestPos.z),
	//		new FVector(mEntity.getPos().x, 0f, mEntity.getPos().z));
	//}
	//else if (MacroDef.XY_MODE)
	//{
	//	dist = FVector.Distance(new FVector(mDestPos.x, mDestPos.y, 0),
	//		new FVector(mEntity.getPos().x, mEntity.getPos().y, 0f));
	//}

	//float deltaSpeed = (mEntity as BeingEntity).getMoveSpeed() * delta;

	//if (dist > deltaSpeed)
	//{
	//	FVector localMove = normal * deltaSpeed;
	//	this->addActorLocalDestOffsetNoOrient(localMove);
	//}
	//else
	//{
	//	mEntity.setPos(this->mDestPos);
	//	this->onArriveDestPos();
	//}
}

// 旋转到目标方向
void BeingEntityMovement::rotateToDest(float delta)
{
	FVector startVec = this->mEntity->getRotateEulerAngle();
	FVector destVec = this->mDestRotate.getRotateEulerAngle();

	// 方向插值
	if (!UtilMath::isEqualVec3(startVec, destVec))
	{
		this->mEntity->setRotate(FQuat::Slerp(this->mEntity->getRotate(), this->mDestRotate.getRotate(), ((BeingEntity*)this->mEntity)->getRotateSpeed() * delta));
	}
	else
	{
		this->onArriveDesRatate();
	}
}

// 旋转到目标方向
void BeingEntityMovement::scaleToDest(float delta)
{
	FVector destScale = this->mEntity->getScale();

	if (!UtilMath::isEqualVec3(this->mDestScale, destScale))
	{
		float dist = 0.0f;

		dist = FVector::Distance(this->mDestScale, this->mEntity->getScale());

		float deltaSpeed = ((BeingEntity*)this->mEntity)->getScaleSpeed() * delta;

		FVector scale = this->mDestScale - this->mEntity->getScale();
		scale.Normalize();

		scale *= deltaSpeed;

		// 如果需要缩放
		if (dist > scale.Size())
		{
			this->mEntity->setScale(this->mEntity->getScale() + scale);
		}
		else
		{
			this->mEntity->setScale(this->mDestScale);
			// 移动到终点
			this->onArriveDestScale();
		}
	}
}

// 到达终点
void BeingEntityMovement::onArriveDestPos()
{
	this->setIsMoveToDest(false);
	((BeingEntity*)this->mEntity)->setBeingState(BeingState::eBSIdle);
}

// 旋转到目标方向
void BeingEntityMovement::onArriveDesRatate()
{
	this->mIsRotateToDest = false;
}

// 缩放到目标带你
void BeingEntityMovement::onArriveDestScale()
{
	this->mIsScaleToDest = false;
}

// 移动到最终地点
//void BeingEntityMovement::moveToPos(FVector destPos)
void BeingEntityMovement::setDestPos(FVector destPos)
{
	if (!UtilMath::isEqualVec3(this->mDestPos, destPos))
	{
		this->mDestPos = destPos;
		FVector destPosRef = this->mEntity->getPos();

		if (!UtilMath::isEqualVec3(this->mDestPos, destPosRef))
		{
			this->setIsMoveToDest(true);

			((BeingEntity*)this->mEntity)->setBeingState(BeingState::eBSWalk);

			// 计算最终方向，太多调用太卡了，暂时不处理方向了
			//this->setDestRotateEulerAngle(UtilMath::getRotateByStartAndEndPoint(this->mEntity.getPos(), this->mDestPos).eulerAngles);
		}
		else
		{
			this->setIsMoveToDest(false);
		}
	}
}

// 直接到具体位置，不用移动
void BeingEntityMovement::gotoPos(FVector destPos)
{
	if (!UtilMath::isEqualVec3(this->mDestPos, destPos))
	{
		this->mDestPos = destPos;
		this->setIsMoveToDest(false);

		FVector destPosRef = this->mEntity->getPos();

		if (!UtilMath::isEqualVec3(this->mDestPos, destPosRef))
		{
			// 计算最终方向
			FQuat quat = UtilMath::getRotateByStartAndEndPoint(this->mEntity->getPos(), this->mDestPos);
			this->setDestRotateEulerAngle(UtilMath::Euler(quat));

			this->mEntity->setRotate(this->mDestRotate.getRotate());
			this->mEntity->setPos(this->mDestPos);
		}
	}
}

void BeingEntityMovement::setDestRotateEulerAngle(FVector destRotate)
{
	// 只能绕 Y 轴旋转
	if (MacroDef::XZ_MODE)
	{
		destRotate.X = 0;
		destRotate.Z = 0;
	}
	else if (MacroDef::XY_MODE)
	{
		// 只能绕 Z 轴旋转
		destRotate.X = 0;
		destRotate.Y = 0;
	}

	this->mDestRotate.setRotateEulerAngle(destRotate);

	FVector euler = this->mEntity->getRotateEulerAngle();

	if (!UtilMath::isEqualVec3(euler, destRotate))
	{
		this->mIsRotateToDest = true;
	}
	else
	{
		this->mIsRotateToDest = false;
	}
}

void BeingEntityMovement::setDestRotate(FQuat destRotate)
{
	// 只能绕 Y 轴旋转
	if (MacroDef::XZ_MODE)
	{
		destRotate.X = 0;
		destRotate.Z = 0;
	}
	else if (MacroDef::XY_MODE)
	{
		// 只能绕 Z 轴旋转
		destRotate.X = 0;
		destRotate.Y = 0;
	}

	this->mDestRotate.setRotation(destRotate);

	FQuat quatRef = this->mEntity->getRotate();

	if (!UtilMath::isEqualQuat(quatRef, destRotate))
	{
		this->mIsRotateToDest = true;
	}
	else
	{
		this->mIsRotateToDest = false;
	}
}

void BeingEntityMovement::setDestScale(float scale)
{
	this->mDestScale = FVector(scale, scale, scale);

	FVector scaleRef = this->mEntity->getScale();

	if (!UtilMath::isEqualVec3(this->mDestScale, scaleRef))
	{
		this->mIsScaleToDest = true;
	}
	else
	{
		this->mIsScaleToDest = false;
	}
}

void BeingEntityMovement::setDestPosAndDestRotate(FVector targetPt, bool immePos, bool immeRotate)
{
	FQuat retQuat = UtilMath::getRotateByStartAndEndPoint(this->mEntity->getPos(), targetPt);
	((BeingEntity*)this->mEntity)->setDestRotateEulerAngle(UtilMath::Euler(retQuat), immeRotate);
	((BeingEntity*)this->mEntity)->setDestRotateEulerAngle(UtilMath::Euler(retQuat), immeRotate);
}

FQuat BeingEntityMovement::getDestRotate()
{
	return this->mDestRotate.getRotate();
}

FVector BeingEntityMovement::getDestPos()
{
	return this->mDestPos;
}

void BeingEntityMovement::setForwardRotate(FVector rotate)
{

}

MY_END_NAMESPACE