#pragma once

#include <string>
#include "GObject.h"
#include "IDispatchObject.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 场景中的实体，定义接口，逻辑相关的一些实现放在 BeingEntity 里面，例如: 地形， Player， Npc
 */
class SceneEntityBase : public GObject, public IDispatchObject, public ITickedObject, public INoOrPriorityObject
{
protected:
	EntityRenderBase* mRender;

	UnityEngine.Vector3 mPos;         // 当前位置信息
	MWrapQuaternion mRotate;   // 当前方向信息
	UnityEngine.Vector3 mScale;       // 当前缩放信息

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
	UnityEngine.GameObject getGameObject();
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
	virtual GameObject gameObject();
	virtual void setGameObject(GameObject rhv);
	virtual void setPos(Vector3 pos);
	virtual void setRenderPos(Vector3 pos);
	UnityEngine.Vector3 getPos();
	// 获取世界空间中的绝对位置
	virtual UnityEngine.Vector3 getFullPos();
	virtual void setRotate(Quaternion rotation);
	// 这个是单位方向向量
	void setRotateNormalDir(UnityEngine.Vector3 normalDir);
	// 这个是欧拉角
	void setRotateEulerAngle(UnityEngine.Vector3 rotation);
	// 获取前向向量
	UnityEngine.Vector3 getForward();
	UnityEngine.Quaternion getRotate();
	UnityEngine.Vector3 getRotateEulerAngle();
	Vector3 getScale();
	virtual void setScale(UnityEngine.Vector3 value);
	void setSelfName(std::string name);
	// 自动管理
	virtual void autoHandle();
	// 初始化渲染器
	virtual void initRender();
	virtual void loadRenderRes();
	EntityRenderBase* getRender();
};

MY_END_NAMESPACE