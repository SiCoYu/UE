#pragma once

#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"		// FQuat
#include "Math/Rotator.h"	// FRotator

#include "SceneEntityMovement.h"
#include "TickMode.h"
#include "MWrapQuaternion.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class BeingEntityMovement : public SceneEntityMovement
{
	M_DECLARE_CLASS(BeingEntityMovement, SceneEntityMovement)

protected:
	FVector mLastPos;         // 之前位置信息
	FQuat mLastRotate;   // 之前方向信息

	FVector mDestPos;         // 目的位置信息
	MWrapQuaternion mDestRotate;   // 目的方向信息，欧拉角
	FVector mDestScale;         // 目标缩放大小

	bool mIsMoveToDest;   // 是否需要移动到目标点
	bool mIsRotateToDest; // 是否需要旋转到目标方向
	bool mIsScaleToDest;  // 是否需要缩放到目标大小

public:
	BeingEntityMovement(SceneEntityBase* entity);
	
	virtual void dispose() override;
	virtual void onPutInPool() override;
	bool isMoveToDest();
	void setIsMoveToDest(bool isMove);
	bool isRotateToDest();
	void setRotateToDest(bool isRotate);

	virtual void onTick(float delta, TickMode tickMode) override;
	// 局部空间移动位置
	virtual void addActorLocalOffset(FVector DeltaLocation);
	// 向目的前向移动
	virtual void addActorLocalDestOffset(FVector DeltaLocation);

	// 向目的前向移动
	virtual void addActorLocalDestOffsetNoOrient(FVector DeltaLocation);
	// 局部空间旋转
	virtual void addLocalRotation(FVector DeltaRotation);
	// 向前移动
	virtual void moveForward();
	// 向左旋转
	void rotateLeft();
	// 向右旋转
	void rotateRight();
	// 停止移动
	virtual void stopMove();
	virtual void stopRotate();
	// 控制向前移动
	void moveForwardToDest(float delta);
	// 自动寻路移动
	void moveToDest(float delta);
	// 移动到目标点，不用判断方向
	void moveToDestNoOrient(float delta);
	// 旋转到目标方向
	void rotateToDest(float delta);
	// 旋转到目标方向
	void scaleToDest(float delta);
	// 到达终点
	virtual void onArriveDestPos();
	// 旋转到目标方向
	void onArriveDesRatate();
	// 缩放到目标带你
	void onArriveDestScale();
	// 移动到最终地点
	//void moveToPos(FVector destPos)
	void setDestPos(FVector destPos);
	// 直接到具体位置，不用移动
	void gotoPos(FVector destPos);
	virtual void setDestRotateEulerAngle(FVector destRotate);
	virtual void setDestRotate(FQuat destRotate);

	void setDestScale(float scale);
	virtual void setDestPosAndDestRotate(FVector targetPt, bool immePos, bool immeRotate);
	FQuat getDestRotate();
	FVector getDestPos();
};

MY_END_NAMESPACE