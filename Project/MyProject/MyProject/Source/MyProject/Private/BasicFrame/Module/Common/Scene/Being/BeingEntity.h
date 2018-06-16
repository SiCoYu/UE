#pragma once

#include <string>
#include "Engine/EngineTypes.h"		// FHitResult

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"		// FQuat
#include "Math/Rotator.h"	// FRotator
#include "BeingState.h"
#include "TickMode.h"
#include "BeingState.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityMovement;
class BeingEntityAttack;

/**
 * @brief 生物 Entity，有感知，可以交互的
 */
class BeingEntity : public SceneEntityBase
{
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

protected:
	float mMoveSpeed;     // 移动速度
	float mRotateSpeed;   // 旋转速度
	float mScaleSpeed;    // 缩放速度

	float mMoveSpeedFactor;   // 移动速度因子
	
	SceneEntityMovement* mMovement;    // 移动组件
	BeingEntityAttack* mAttack;
	//protected HudItemBase mHud;     // HUD

	std::string mName;         // 名字
	//BeingAnimatorControl mAnimatorControl;
	std::string mPrefabPath;   // 预制的目录

	//protected FVector mHudPos;
	BeingState mBeingState;
	BeingSubState mBeingSubState;

public:
	BeingEntity();
	virtual void onDestroy() override;
	virtual void onPutInPool() override;

	virtual void setMoveSpeed(float value);
	float getMoveSpeed(bool isOrig = false);
	void setRotateSpeed(float value);
	float getRotateSpeed();

	void setScaleSpeed(float value);
	float getScaleSpeed();
	virtual void setDestPos(FVector pos, bool immePos);
	FVector getDestPos();
	void setDestRotateEulerAngle(FVector rotate, bool immeRotate);
	void setDestRotate(FQuat rotate, bool immeRotate);
	void setDestPosAndDestRotate(FVector targetPt, bool immePos, bool immeRotate);
	void setDestScale(float scale, bool immeScale);
	// 设置前向旋转
	void setForwardRotate(FVector rotate);

	virtual void setName(std::string name);
	std::string getName();

protected:
	virtual void _onPreInit() override;
	virtual void _onPostInit() override;

public:
	virtual void loadRenderRes() override;
	virtual void onTick(float delta, TickMode tickMode) override;

protected:
	// Tick 第一阶段执行
	virtual void _onPreTick(float delta, TickMode tickMode) override;
	// Tick 第二阶段执行
	virtual void _onPostTick(float delta, TickMode tickMode) override;

public:
	// 获取 Hud 场景中的位置
	//virtual FVector getHudPos();
	virtual void setBeingState(BeingState state);
	BeingState getBeingState();
	void setBeingSubState(BeingSubState subState);

	BeingSubState getBeingSubState();
	void clearBeingSubState();
	void overlapToEnter(BeingEntity bBeingEntity, const FHitResult& SweepResult);
	void overlapToStay(BeingEntity bBeingEntity, const FHitResult& SweepResult);
	void overlapToExit(BeingEntity bBeingEntity, const FHitResult& SweepResult);

	FQuat getDestRotate();
	// 预制目录是否有效
	bool isPrefabPathValid();
	void setPrefabPath(std::string path);
	std::string getPrefabPath();
	// 关联到父节点
	virtual void attachToParentNode(SceneEntityRenderBase* render);
	void setMoveSpeedFactor(float value);
};

MY_END_NAMESPACE