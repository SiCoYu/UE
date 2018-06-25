#pragma once

#include <string>
#include "GObject.h"
#include "IDispatchObject.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "Math/Vector.h"			// FVector
#include "Math/Quat.h"				// FQuat
#include "Math/Rotator.h"			// FRotator
#include "GameFramework/Actor.h"	// AActor
#include "MWrapQuaternion.h"	// AActor
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityRenderBase;

/**
 * @brief 场景中的实体，定义接口，逻辑相关的一些实现放在 BeingEntity 里面，例如: 地形， Player， Npc
 */
class SceneEntityBase : public GObject/*, public IDispatchObject*//*, public ITickedObject*//*, public INoOrPriorityObject*/
{
	M_DECLARE_CLASS(SceneEntityBase, GObject)

protected:
	SceneEntityRenderBase* mRender;

	FVector mPos;			// 当前位置信息
	MWrapQuaternion mRotate;			// 当前方向信息
	FVector mScale;			// 当前缩放信息

	bool mIsVisible;          // 是否可见，数据是否可见
	uint mThisId;             // 唯一 Id

public:
	SceneEntityBase();
	// 这个接口调用之前，一定要先设置 ThisId ，调用 setThisId，必须先设置这个
	virtual void init();

protected:
	virtual void _onPreInit();
	virtual void _onExecInit();
	virtual void _onPostInit();

public:
	virtual void onInit();
	// 释放接口
	virtual void dispose();
	// 释放的时候回调的接口
	virtual void onDestroy();
	// 缓存回收
	virtual void onPutInPool();
	virtual void onGetFromPool();
	virtual void show();
	virtual void hide();
	virtual bool IsVisible();
	virtual void setClientDispose(bool isDispose);
	AActor* getActor();
	// 每一帧执行
	virtual void onTick(float delta, TickMode tickMode);
	
protected:
	// Tick 第一阶段执行
	virtual void _onPreTick(float delta, TickMode tickMode);
	virtual void _onExecTick(float delta, TickMode tickMode);
	// Tick 第二阶段执行
	virtual void _onPostTick(float delta, TickMode tickMode);
	
public:
	uint getThisId();
	virtual AActor* gameObject();
	virtual void setGameObject(AActor* rhv);
	virtual void setPos(FVector pos);
	virtual void setRenderPos(FVector pos);
	FVector getPos();
	// 获取世界空间中的绝对位置
	virtual FVector getFullPos();
	virtual void setRotate(FQuat rotation);
	// 这个是单位方向向量
	void setRotateNormalDir(FVector normalDir);
	// 这个是欧拉角
	void setRotateEulerAngle(FVector rotation);
	// 获取前向向量
	FVector getForward();
	FQuat getRotate();
	FVector getRotateEulerAngle();
	FVector getScale();
	virtual void setScale(FVector value);
	void setSelfName(std::string name);
	// 自动管理
	virtual void autoHandle();
	// 初始化渲染器
	virtual void initRender();
	virtual void loadRenderRes();
	SceneEntityRenderBase* getRender();
};

MY_END_NAMESPACE