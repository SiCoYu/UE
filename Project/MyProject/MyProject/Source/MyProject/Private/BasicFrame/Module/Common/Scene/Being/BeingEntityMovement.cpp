#include "MyProject.h"
#include "BeingEntityMovement.h"
#include "SceneEntityBase.h"
#include "BeingEntity.h"
#include "MWrapQuaternion.h"
#include "UtilMath.h"
#include "Ctx.h"
#include "SystemTimeData.h"
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
	//float delta = Ctx.msInstance.mSystemTimeData.getFixedTimestep();
	//FVector deltaRotation = new FVector(0.0f, -(mEntity as BeingEntity).getRotateSpeed() * delta, 0.0f);
	//this->addLocalRotation(deltaRotation);
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
	//FVector localMove = UtilEngineWrap.convPosByMode(new FVector(0.0f, 0.0f, (mEntity as BeingEntity).getMoveSpeed() * delta));
	//this->addActorLocalOffset(localMove);
}

// 自动寻路移动
void BeingEntityMovement::moveToDest(float delta)
{
	//if (MacroDef.DRAW_DEBUG)
	//{
	//	UtilEngineWrap.DrawLine(mEntity.getPos(), mDestPos, UnityEngine.Color.red);
	//}

	//float dist = 0.0f;

	//if (MacroDef.XZ_MODE)
	//{
	//	dist = FVector.Distance(new FVector(mDestPos.x, 0f, mDestPos.z),
	//			new FVector(mEntity.getPos().x, 0f, mEntity.getPos().z));
	//}
	//else if (MacroDef.XY_MODE)
	//{
	//	dist = FVector.Distance(new FVector(mDestPos.x, mDestPos.y, 0),
	//			new FVector(mEntity.getPos().x, mEntity.getPos().y, 0f));
	//}

	//float deltaSpeed = (mEntity as BeingEntity).getMoveSpeed() * delta;

	//if (dist > deltaSpeed)
	//{
	//	FVector localMove = UtilEngineWrap.convPosByMode(new FVector(0.0f, 0.0f, (mEntity as BeingEntity).getMoveSpeed() * delta));
	//	this->addActorLocalDestOffset(localMove);
	//}
	//else
	//{
	//	mEntity.setPos(this->mDestPos);
	//	this->onArriveDestPos();
	//}
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
	// 方向插值
	//if (!UtilMath::isEqualVec3(mEntity.getRotateEulerAngle(), this->mDestRotate.getRotateEulerAngle()))
	//{
	//	mEntity.setRotate(FQuat.Slerp(mEntity.getRotate(), this->mDestRotate.getRotate(), (mEntity as BeingEntity).getRotateSpeed() * delta));
	//}
	//else
	//{
	//	this->onArriveDesRatate();
	//}
}

// 旋转到目标方向
void BeingEntityMovement::scaleToDest(float delta)
{
	//if (!UtilMath::isEqualVec3(this->mDestScale, this->mEntity.getScale()))
	//{
	//	float dist = 0.0f;
	//	dist = FVector.Distance(this->mDestScale, this->mEntity.getScale());

	//	float deltaSpeed = (mEntity as BeingEntity).getScaleSpeed() * delta;

	//	FVector scale = this->mDestScale - mEntity.getScale();
	//	scale.Normalize();

	//	scale *= deltaSpeed;

	//	// 如果需要缩放
	//	if (dist > scale.magnitude)
	//	{
	//		mEntity.setScale(mEntity.getScale() + scale);
	//	}
	//	else
	//	{
	//		mEntity.setScale(this->mDestScale);
	//		// 移动到终点
	//		this->onArriveDestScale();
	//	}
	//}
}

// 到达终点
void BeingEntityMovement::onArriveDestPos()
{
	//this->setIsMoveToDest(false);
	//((BeingEntity*)this->mEntity)->setBeingState(BeingState::eBSIdle);
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
	//if (!UtilMath::isEqualVec3(this->mDestPos, destPos))
	//{
	//	destPos = Ctx.msInstance.mSceneSys.adjustPosInRange(this->mEntity, destPos);

	//	this->mDestPos = destPos;

	//	if (!UtilMath::isEqualVec3(mDestPos, mEntity.getPos()))
	//	{
	//		this->setIsMoveToDest(true);
	//		this->mMoveWay = MoveWay.eAutoPathMove;

	//		(this->mEntity as BeingEntity).setBeingState(BeingState.eBSWalk);

	//		// 计算最终方向，太多调用太卡了，暂时不处理方向了
	//		//this->setDestRotateEulerAngle(UtilMath::getRotateByStartAndEndPoint(this->mEntity.getPos(), this->mDestPos).eulerAngles);
	//	}
	//	else
	//	{
	//		this->setIsMoveToDest(false);
	//	}
	//}
}

// 直接到具体位置，不用移动
void BeingEntityMovement::gotoPos(FVector destPos)
{
	//if (!UtilMath::isEqualVec3(this->mDestPos, destPos))
	//{
	//	destPos = Ctx.msInstance.mSceneSys.adjustPosInRange(this->mEntity, destPos);

	//	this->mDestPos = destPos;
	//	this->setIsMoveToDest(false);

	//	if (!UtilMath::isEqualVec3(mDestPos, mEntity.getPos()))
	//	{
	//		// 计算最终方向
	//		this->setDestRotateEulerAngle(UtilMath::getRotateByStartAndEndPoint(this->mEntity.getPos(), this->mDestPos).eulerAngles);
	//		this->mEntity.setRotate(this->mDestRotate.getRotate());
	//		this->mEntity.setPos(this->mDestPos);

	//		this->sendMoveMsg();
	//	}
	//}
}

void BeingEntityMovement::setDestRotateEulerAngle(FVector destRotate)
{
	//// 只能绕 Y 轴旋转
	//if (MacroDef.XZ_MODE)
	//{
	//	destRotate.x = 0;
	//	destRotate.z = 0;
	//}
	//else if (MacroDef.XY_MODE)
	//{
	//	// 只能绕 Z 轴旋转
	//	destRotate.x = 0;
	//	destRotate.y = 0;
	//}

	//this->mDestRotate.setRotateEulerAngle(destRotate);

	//if (!UtilMath::isEqualVec3(mEntity.getRotateEulerAngle(), destRotate))
	//{
	//	this->mIsRotateToDest = true;
	//}
	//else
	//{
	//	this->mIsRotateToDest = false;
	//}
}

void BeingEntityMovement::setDestRotate(FQuat destRotate)
{
	//// 只能绕 Y 轴旋转
	//if (MacroDef.XZ_MODE)
	//{
	//	destRotate.x = 0;
	//	destRotate.z = 0;
	//}
	//else if (MacroDef.XY_MODE)
	//{
	//	// 只能绕 Z 轴旋转
	//	destRotate.x = 0;
	//	destRotate.y = 0;
	//}

	//this->mDestRotate.setRotation(destRotate);

	//if (!UtilMath::isEqualQuat(mEntity.getRotate(), destRotate))
	//{
	//	this->mIsRotateToDest = true;
	//}
	//else
	//{
	//	this->mIsRotateToDest = false;
	//}
}

void BeingEntityMovement::setDestScale(float scale)
{
	//if(UtilMath::isInvalidNum(scale))
	//{
	//	if (MacroDef.ENABLE_LOG)
	//	{
	//		Ctx.msInstance.mLogSys.log("Invalid num", LogTypeId.eLogCommon);
	//	}
	//}
	//this->mDestScale = new FVector(scale, scale, scale);

	//if (!UtilMath::isEqualVec3(this->mDestScale, this->mEntity.getScale()))
	//{
	//	this->mIsScaleToDest = true;
	//}
	//else
	//{
	//	this->mIsScaleToDest = false;
	//}
}

void BeingEntityMovement::setDestPosAndDestRotate(FVector targetPt, bool immePos, bool immeRotate)
{
	//FQuat retQuat = UtilMath::getRotateByStartAndEndPoint(this->mEntity.getPos(), targetPt);
	//(this->mEntity as BeingEntity).setDestRotateEulerAngle(retQuat.eulerAngles, immeRotate);
	//(this->mEntity as BeingEntity).setDestRotateEulerAngle(retQuat.eulerAngles, immeRotate);
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