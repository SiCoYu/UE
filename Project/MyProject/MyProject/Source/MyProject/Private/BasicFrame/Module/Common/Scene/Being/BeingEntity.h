#pragma once

#include <string>
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

	//protected UnityEngine.Vector3 mHudPos;

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
	virtual void setDestPos(UnityEngine.Vector3 pos, bool immePos);
	UnityEngine.Vector3 getDestPos();
	void setDestRotateEulerAngle(UnityEngine.Vector3 rotate, bool immeRotate);
	void setDestRotate(UnityEngine.Quaternion rotate, bool immeRotate);
	void setDestPosAndDestRotate(UnityEngine.Vector3 targetPt, bool immePos, bool immeRotate);
	void setDestScale(float scale, bool immeScale);
	// 设置前向旋转
	void setForwardRotate(UnityEngine.Vector3 rotate);

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
	//virtual UnityEngine.Vector3 getHudPos();
	virtual void setBeingState(BeingState state);
	BeingState getBeingState();
	void setBeingSubState(BeingSubState subState);

	BeingSubState getBeingSubState();
	void clearBeingSubState();
	void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo);
	void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo);
	void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo);
	void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo);
	void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo);
	void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo);

	UnityEngine.Quaternion getDestRotate();
	// 预制目录是否有效
	bool isPrefabPathValid();
	void setPrefabPath(std::string path);
	std::string getPrefabPath();
	// 关联到父节点
	virtual void attachToParentNode(EntityRenderBase* render);
	void setMoveSpeedFactor(float value);
};

MY_END_NAMESPACE