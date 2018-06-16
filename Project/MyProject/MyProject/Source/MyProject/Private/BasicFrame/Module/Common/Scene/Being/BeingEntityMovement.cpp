#include "MyProject.h"
#include "BeingEntityMovement.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

BeingEntityMovement::BeingEntityMovement(SceneEntityBase* entity)
	: base(entity)
{
	this.mDestRotate = new MWrapQuaternion(0, 0, 0, 1);
	this.mIsMoveToDest = false;
	this.mIsRotateToDest = false;
	this.mIsScaleToDest = false;
}

void BeingEntityMovement::dispose()
{
	base.dispose();
}

void BeingEntityMovement::onPutInPool()
{
	this.mIsMoveToDest = false;
	this.mIsRotateToDest = false;
	this.mIsScaleToDest = false;

	this.mLastPos = UtilMath.ZeroVec3;
	this.mLastRotate = UtilMath.UnitQuat;

	this.mDestPos = UtilMath.ZeroVec3;
	this.mDestRotate.setRotation(UtilMath.UnitQuat);
	this.mDestScale = UtilMath.ZeroVec3;
	this.mDestRotate.clear();

	base.onPutInPool();
}

bool BeingEntityMovement::isMoveToDest()
{
	return this.mIsMoveToDest;
}

void BeingEntityMovement::setIsMoveToDest(bool isMove)
{
	if (this.mIsMoveToDest != isMove)
	{
		this.mIsMoveToDest = isMove;

		if(false == this.mIsMoveToDest)
		{
			this.mMoveWay = MoveWay.eNone;
		}
	}
}

bool BeingEntityMovement::isRotateToDest()
{
	return this.mIsRotateToDest;
}

void BeingEntityMovement::setRotateToDest(bool isRotate)
{
	if (this.mIsRotateToDest != isRotate)
	{
		this.mIsRotateToDest = isRotate;
	}
}

void BeingEntityMovement::onTick(float delta, TickMode tickMode)
{
	base.onTick(delta, tickMode);

	if (this.mIsRotateToDest)
	{
		this.rotateToDest(delta);
	}

	if (this.mIsScaleToDest)
	{
		this.scaleToDest(delta);
	}

	if (this.mIsMoveToDest)
	{
		// 设置前向方向移动
		this.moveForwardToDest(delta);
	}
}

// 局部空间移动位置
void BeingEntityMovement::addActorLocalOffset(UnityEngine.Vector3 DeltaLocation)
{
	UnityEngine.Vector3 localOffset = mEntity.getRotate() * DeltaLocation;
	mEntity.setPos(mEntity.getPos() + localOffset);

	this.sendMoveMsg();
}

// 向目的前向移动
void BeingEntityMovement::addActorLocalDestOffset(UnityEngine.Vector3 DeltaLocation)
{
	UnityEngine.Vector3 localOffset = this.mDestRotate.getRotate() * DeltaLocation;
	mEntity.setPos(mEntity.getPos() + localOffset);

	this.sendMoveMsg();
}

// 向目的前向移动
void BeingEntityMovement::addActorLocalDestOffsetNoOrient(UnityEngine.Vector3 DeltaLocation)
{
	UnityEngine.Vector3 localOffset = DeltaLocation;
	mEntity.setPos(mEntity.getPos() + localOffset);

	this.sendMoveMsg();
}

// 局部空间旋转
void BeingEntityMovement::addLocalRotation(UnityEngine.Vector3 DeltaRotation)
{
	this.mEntity.setRotate(mEntity.getRotate() * UtilEngineWrap.convQuatFromEuler(DeltaRotation));

	this.sendMoveMsg();
}

// 向前移动
void BeingEntityMovement::moveForward()
{
	if (BeingState.eBSWalk != (this.mEntity as BeingEntity).getBeingState())
	{
		(this.mEntity as BeingEntity).setBeingState(BeingState.eBSWalk);
		this.setIsMoveToDest(true);
		this.mMoveWay = MoveWay.eIOControlMove;
	}
}

// 向左旋转
void BeingEntityMovement::rotateLeft()
{
	float delta = Ctx.msInstance.mSystemTimeData.getFixedTimestep();
	UnityEngine.Vector3 deltaRotation = new UnityEngine.Vector3(0.0f, (mEntity as BeingEntity).getRotateSpeed() * delta, 0.0f);
	this.addLocalRotation(deltaRotation);
}

// 向右旋转
void BeingEntityMovement::rotateRight()
{
	//(this.mEntity as BeingEntity).setBeingState(BeingState.BSWalk);

	float delta = Ctx.msInstance.mSystemTimeData.getFixedTimestep();
	UnityEngine.Vector3 deltaRotation = new UnityEngine.Vector3(0.0f, -(mEntity as BeingEntity).getRotateSpeed() * delta, 0.0f);
	this.addLocalRotation(deltaRotation);
}

// 停止移动
void BeingEntityMovement::stopMove()
{
	
}

void BeingEntityMovement::stopRotate()
{
	this.setRotateToDest(false);
}

// 控制向前移动
void BeingEntityMovement::moveForwardToDest(float delta)
{
	UnityEngine.Vector3 localMove = UtilEngineWrap.convPosByMode(new UnityEngine.Vector3(0.0f, 0.0f, (mEntity as BeingEntity).getMoveSpeed() * delta));
	this.addActorLocalOffset(localMove);
}

// 自动寻路移动
void BeingEntityMovement::moveToDest(float delta)
{
	if (MacroDef.DRAW_DEBUG)
	{
		UtilEngineWrap.DrawLine(mEntity.getPos(), mDestPos, UnityEngine.Color.red);
	}

	//this.checkAndUpdateDestRotate();

	float dist = 0.0f;

	if (MacroDef.XZ_MODE)
	{
		dist = UnityEngine.Vector3.Distance(new UnityEngine.Vector3(mDestPos.x, 0f, mDestPos.z),
				new UnityEngine.Vector3(mEntity.getPos().x, 0f, mEntity.getPos().z));
	}
	else if (MacroDef.XY_MODE)
	{
		dist = UnityEngine.Vector3.Distance(new UnityEngine.Vector3(mDestPos.x, mDestPos.y, 0),
				new UnityEngine.Vector3(mEntity.getPos().x, mEntity.getPos().y, 0f));
	}

	float deltaSpeed = (mEntity as BeingEntity).getMoveSpeed() * delta;

	if (dist > deltaSpeed)
	{
		UnityEngine.Vector3 localMove = UtilEngineWrap.convPosByMode(new UnityEngine.Vector3(0.0f, 0.0f, (mEntity as BeingEntity).getMoveSpeed() * delta));
		this.addActorLocalDestOffset(localMove);
	}
	else
	{
		mEntity.setPos(this.mDestPos);
		this.onArriveDestPos();
	}
}

// 移动到目标点，不用判断方向
void BeingEntityMovement::moveToDestNoOrient(float delta)
{
	if (MacroDef.DRAW_DEBUG)
	{
		UtilEngineWrap.DrawLine(mEntity.getPos(), mDestPos, UnityEngine.Color.red);
	}

	UnityEngine.Vector3 normal = mDestPos - mEntity.getPos();
	normal.Normalize();

	float dist = 0.0f;
	if (MacroDef.XZ_MODE)
	{
		dist = UnityEngine.Vector3.Distance(new UnityEngine.Vector3(mDestPos.x, 0f, mDestPos.z),
			new UnityEngine.Vector3(mEntity.getPos().x, 0f, mEntity.getPos().z));
	}
	else if (MacroDef.XY_MODE)
	{
		dist = UnityEngine.Vector3.Distance(new UnityEngine.Vector3(mDestPos.x, mDestPos.y, 0),
			new UnityEngine.Vector3(mEntity.getPos().x, mEntity.getPos().y, 0f));
	}

	float deltaSpeed = (mEntity as BeingEntity).getMoveSpeed() * delta;

	if (dist > deltaSpeed)
	{
		UnityEngine.Vector3 localMove = normal * deltaSpeed;
		this.addActorLocalDestOffsetNoOrient(localMove);
	}
	else
	{
		mEntity.setPos(this.mDestPos);
		this.onArriveDestPos();
	}
}

// 旋转到目标方向
void BeingEntityMovement::rotateToDest(float delta)
{
	// 方向插值
	if (!UtilMath.isEqualVec3(mEntity.getRotateEulerAngle(), this.mDestRotate.getRotateEulerAngle()))
	{
		mEntity.setRotate(UnityEngine.Quaternion.Slerp(mEntity.getRotate(), this.mDestRotate.getRotate(), (mEntity as BeingEntity).getRotateSpeed() * delta));
	}
	else
	{
		this.onArriveDesRatate();
	}
}

// 旋转到目标方向
void BeingEntityMovement::scaleToDest(float delta)
{
	if (!UtilMath.isEqualVec3(this.mDestScale, this.mEntity.getScale()))
	{
		float dist = 0.0f;
		dist = UnityEngine.Vector3.Distance(this.mDestScale, this.mEntity.getScale());

		float deltaSpeed = (mEntity as BeingEntity).getScaleSpeed() * delta;

		UnityEngine.Vector3 scale = this.mDestScale - mEntity.getScale();
		scale.Normalize();

		scale *= deltaSpeed;

		// 如果需要缩放
		if (dist > scale.magnitude)
		{
			mEntity.setScale(mEntity.getScale() + scale);
		}
		else
		{
			mEntity.setScale(this.mDestScale);
			// 移动到终点
			this.onArriveDestScale();
		}
	}
}

// 到达终点
void BeingEntityMovement::onArriveDestPos()
{
	this.setIsMoveToDest(false);
	(this.mEntity as BeingEntity).setBeingState(BeingState.eBSIdle);
}

// 旋转到目标方向
void BeingEntityMovement::onArriveDesRatate()
{
	this.mIsRotateToDest = false;
}

// 缩放到目标带你
void BeingEntityMovement::onArriveDestScale()
{
	this.mIsScaleToDest = false;
}

// 移动到最终地点
//void BeingEntityMovement::moveToPos(UnityEngine.Vector3 destPos)
void BeingEntityMovement::setDestPos(UnityEngine.Vector3 destPos)
{
	if (!UtilMath.isEqualVec3(this.mDestPos, destPos))
	{
		destPos = Ctx.msInstance.mSceneSys.adjustPosInRange(this.mEntity, destPos);

		this.mDestPos = destPos;

		if (!UtilMath.isEqualVec3(mDestPos, mEntity.getPos()))
		{
			this.setIsMoveToDest(true);
			this.mMoveWay = MoveWay.eAutoPathMove;

			(this.mEntity as BeingEntity).setBeingState(BeingState.eBSWalk);

			// 计算最终方向，太多调用太卡了，暂时不处理方向了
			//this.setDestRotateEulerAngle(UtilMath.getRotateByStartAndEndPoint(this.mEntity.getPos(), this.mDestPos).eulerAngles);
		}
		else
		{
			this.setIsMoveToDest(false);
		}
	}
}

// 直接到具体位置，不用移动
void BeingEntityMovement::gotoPos(UnityEngine.Vector3 destPos)
{
	if (!UtilMath.isEqualVec3(this.mDestPos, destPos))
	{
		destPos = Ctx.msInstance.mSceneSys.adjustPosInRange(this.mEntity, destPos);

		this.mDestPos = destPos;
		this.setIsMoveToDest(false);

		if (!UtilMath.isEqualVec3(mDestPos, mEntity.getPos()))
		{
			// 计算最终方向
			this.setDestRotateEulerAngle(UtilMath.getRotateByStartAndEndPoint(this.mEntity.getPos(), this.mDestPos).eulerAngles);
			this.mEntity.setRotate(this.mDestRotate.getRotate());
			this.mEntity.setPos(this.mDestPos);

			this.sendMoveMsg();
		}
	}
}

void BeingEntityMovement::setDestRotateEulerAngle(UnityEngine.Vector3 destRotate)
{
	// 只能绕 Y 轴旋转
	if (MacroDef.XZ_MODE)
	{
		destRotate.x = 0;
		destRotate.z = 0;
	}
	else if (MacroDef.XY_MODE)
	{
		// 只能绕 Z 轴旋转
		destRotate.x = 0;
		destRotate.y = 0;
	}

	this.mDestRotate.setRotateEulerAngle(destRotate);

	if (!UtilMath.isEqualVec3(mEntity.getRotateEulerAngle(), destRotate))
	{
		this.mIsRotateToDest = true;
	}
	else
	{
		this.mIsRotateToDest = false;
	}
}

void BeingEntityMovement::setDestRotate(UnityEngine.Quaternion destRotate)
{
	// 只能绕 Y 轴旋转
	if (MacroDef.XZ_MODE)
	{
		destRotate.x = 0;
		destRotate.z = 0;
	}
	else if (MacroDef.XY_MODE)
	{
		// 只能绕 Z 轴旋转
		destRotate.x = 0;
		destRotate.y = 0;
	}

	this.mDestRotate.setRotation(destRotate);

	if (!UtilMath.isEqualQuat(mEntity.getRotate(), destRotate))
	{
		this.mIsRotateToDest = true;
	}
	else
	{
		this.mIsRotateToDest = false;
	}
}

void BeingEntityMovement::setDestScale(float scale)
{
	if(UtilMath.isInvalidNum(scale))
	{
		if (MacroDef.ENABLE_LOG)
		{
			Ctx.msInstance.mLogSys.log("Invalid num", LogTypeId.eLogCommon);
		}
	}
	this.mDestScale = new UnityEngine.Vector3(scale, scale, scale);

	if (!UtilMath.isEqualVec3(this.mDestScale, this.mEntity.getScale()))
	{
		this.mIsScaleToDest = true;
	}
	else
	{
		this.mIsScaleToDest = false;
	}
}

void BeingEntityMovement::setDestPosAndDestRotate(UnityEngine.Vector3 targetPt, bool immePos, bool immeRotate)
{
	UnityEngine.Quaternion retQuat = UtilMath.getRotateByStartAndEndPoint(this.mEntity.getPos(), targetPt);
	(this.mEntity as BeingEntity).setDestRotateEulerAngle(retQuat.eulerAngles, immeRotate);
	(this.mEntity as BeingEntity).setDestRotateEulerAngle(retQuat.eulerAngles, immeRotate);
}

UnityEngine.Quaternion BeingEntityMovement::getDestRotate()
{
	return this.mDestRotate.getRotate();
}

UnityEngine.Vector3 BeingEntityMovement::getDestPos()
{
	return this.mDestPos;
}

MY_END_NAMESPACE