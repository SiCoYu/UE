#pragma once

#include <string>
#include "GObject.h"
#include "IDispatchObject.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 场景中的实体，定义接口，逻辑相关的一些实现放在 BeingEntity 里面，例如: 地形， Player， Npc
 */
public class SceneEntityBase : GObject, IDispatchObject, ITickedObject, INoOrPriorityObject
{
protected:
	EntityRenderBase* mRender;
	EntityType mEntityType;   // Entity 类型
	string mEntityUniqueId;   // Entity 唯一 Id

	UnityEngine.Vector3 mPos;         // 当前位置信息
	MWrapQuaternion mRotate;   // 当前方向信息
	UnityEngine.Vector3 mScale;       // 当前缩放信息

	bool mIsVisible;          // 是否可见，数据是否可见
	uint mThisId;             // 唯一 Id

public:
	SceneEntityBase()
	{
		this.mRotate = new MWrapQuaternion(0, 0, 0, 1);
		this.mRender = null;
		this.onGetFromPool();
	}

	// 这个接口调用之前，一定要先设置 ThisId ，调用 setThisId，必须先设置这个
	virtual void init()
	{
		this.onInit();
	}

protected:
	virtual void _onPreInit()
	{

	}

	virtual void _onExecInit()
	{

	}

	virtual void _onPostInit()
	{

	}

public:
	virtual void onInit()
	{
		this._onPreInit();
		this._onExecInit();
		this._onPostInit();
	}

	// 释放接口
	virtual void dispose()
	{
		this.onDestroy();
	}

	// 释放的时候回调的接口
	virtual void onDestroy()
	{
		if (null != this.mRender)
		{
			this.mRender.dispose();
			this.mRender = null;
		}

		if(null != this.mTDTile)
		{
			this.mTDTile.removeEntity(this);
			this.mTDTile = null;
		}

		this.setClientDispose(true);
	}

	// 缓存回收
	virtual void onPutInPool()
	{
		this.mIsInPoolOrDispose = true;

		if (null != this.mRender)
		{
			this.mRender.putInPool();
		}

		this.mRotate.clear();
	}

	virtual void onGetFromPool()
	{
		this.mPos = UtilMath.ZeroVec3;
		this.mRotate.setRotateXYZW(0, 0, 0, 1);
		this.mScale = Vector3.one;

		this.mIsVisible = false;        // 当前逻辑是否可见
	}

	virtual void show()
	{
		if (!this.mIsVisible)
		{
			this.mIsVisible = true;
			//this.mIsInScreenRange = true;   // 显示不一定在 Screen 可见

			if (null != this.mRender)
			{
				this.mRender.show();
			}

			this.onClipShow();
		}
	}

	virtual void hide()
	{
		if (this.mIsVisible)
		{
			this.mIsVisible = false;
			this.mIsClipVisible = false;  // 逻辑隐藏，直接设定不在屏幕范围内

			if (null != this.mRender)
			{
				this.mRender.hide();
			}

			this.onClipHide();
		}
	}

	virtual bool IsVisible()
	{
		return this.mIsVisible;
	}

	virtual void setClientDispose(bool isDispose)
	{
		if (null != this.mRender)
		{
			this.mRender.setClientDispose(isDispose);
		}
	}

	UnityEngine.GameObject getGameObject()
	{
		if(null != this.mRender)
		{
			return this.mRender.getSelfActor();
		}

		return null;
	}

	// 每一帧执行
	virtual void onTick(float delta, TickMode tickMode)
	{
		this._onPreTick(delta, tickMode);
		this._onExecTick(delta, tickMode);
		this._onPostTick(delta, tickMode);
		if(null != this.mRender) this.mRender.onTick(delta, tickMode);
	}

protected:
	// Tick 第一阶段执行
	virtual void _onPreTick(float delta, TickMode tickMode)
	{

	}

	virtual void _onExecTick(float delta, TickMode tickMode)
	{

	}

	// Tick 第二阶段执行
	virtual void _onPostTick(float delta, TickMode tickMode)
	{

	}

public:
	virtual GameObject gameObject()
	{
		if (null != this.mRender)
		{
			return this.mRender.getSelfActor();
		}

		return null;
	}

	virtual void setGameObject(GameObject rhv)
	{
		if (null != this.mRender)
		{
			this.mRender.setSelfActor(rhv);
		}
	}

	virtual void setPos(Vector3 pos)
	{
		if (!UtilMath.isEqualVec3(this.mPos, pos) || this.mIsFirst)
		{
			this.mIsFirst = false;
			pos = Ctx.msInstance.mSceneSys.adjustPosInRange(this, pos);

			this.mPos = pos;

			if (null != this.mRender)
			{
				this.mRender.setPos(pos);
			}

			if (MacroDef.ENABLE_SCENE2D_CLIP)
			{
				this.updateClip();
			}

			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setPos, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}", this.getBasicInfoStr(), this.mPos.x, this.mPos.y, this.mPos.z), LogTypeId.eLogBeingMove);
			}
		}
	}

	virtual void setRenderPos(Vector3 pos)
	{
		if (!UtilEngineWrap.isInFakePos(pos) && !UtilMath.isEqualVec3(this.mPos, pos))
		{
			this.mPos = pos;

			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRenderPos, BasicInfo is {0}, mPosX = {1}, mPosY = {2}, mPosZ = {3}", this.getBasicInfoStr(), this.mPos.x, this.mPos.y, this.mPos.z), LogTypeId.eLogBeingMove);
			}
		}
	}

	UnityEngine.Vector3 getPos()
	{
		return this.mPos;
	}

	// 获取世界空间中的绝对位置
	virtual UnityEngine.Vector3 getFullPos()
	{
		return this.mPos;
	}

	virtual void setRotate(Quaternion rotation)
	{
		if (!UtilMath.isEqualQuat(this.mRotate.getRotate(), rotation))
		{
			this.mRotate.setRotation(rotation);

			// Player 是不更新转换的, FlyBulletFlock 也是不更新的
			if (EntityType.eFlyBulletFlock != this.mEntityType &&
				EntityType.ePlayerMain != this.getEntityType() &&
				EntityType.ePlayerOther != this.getEntityType())
			{
				if (null != this.mRender)
				{
					this.mRender.setRotate(rotation);
				}
			}

			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRotation, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}, W = {4}", this.getBasicInfoStr(), this.mRotate.getX(), this.mRotate.getY(), this.mRotate.getZ(), this.mRotate.getW()), LogTypeId.eLogBeingMove);
			}
		}
	}

	// 这个是单位方向向量
	void setRotateNormalDir(UnityEngine.Vector3 normalDir)
	{
		UnityEngine.Quaternion quad = UtilMath.getRotateByOrient(normalDir);
		this.setRotateEulerAngle(quad.eulerAngles);
	}

	// 这个是欧拉角
	void setRotateEulerAngle(UnityEngine.Vector3 rotation)
	{
		if (!UtilMath.isEqualVec3(this.mRotate.getRotateEulerAngle(), rotation))
		{
			// 只能绕 Y 轴旋转
			if (MacroDef.XZ_MODE)
			{
				rotation.x = 0;
				rotation.z = 0;
			}
			else if (MacroDef.XY_MODE)
			{
				// 只能绕 Z 轴旋转
				rotation.x = 0;
				rotation.y = 0;
			}

			this.mRotate.setRotateEulerAngle(rotation);

			// Player 是不更新转换的
			if (EntityType.ePlayerMain != this.getEntityType() &&
				EntityType.ePlayerOther != this.getEntityType() &&
				EntityType.eFlyBulletFlock != this.getEntityType())
			{
				if (null != this.mRender)
				{
					this.mRender.setRotate(this.mRotate.getRotate());
				}
			}

			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRotateEulerAngle, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}, W = {4}", this.getBasicInfoStr(), this.mRotate.getX(), this.mRotate.getY(), this.mRotate.getZ(), this.mRotate.getW()), LogTypeId.eLogBeingMove);
			}
		}
	}

	// 获取前向向量
	UnityEngine.Vector3 getForward()
	{
		UnityEngine.Vector3 forward = this.mRotate.getRotate() * UnityEngine.Vector3.forward;

		return forward;
	}

	UnityEngine.Quaternion getRotate()
	{
		return this.mRotate.getRotate();
	}

	UnityEngine.Vector3 getRotateEulerAngle()
	{
		return this.mRotate.getRotateEulerAngle();
	}

	Vector3 getScale()
	{
		return this.mScale;
	}

	virtual void setScale(UnityEngine.Vector3 value)
	{
		if (!UtilMath.isEqualVec3(this.mScale, value))
		{
			this.mScale = value;

			if (null != this.mRender)
			{
				this.mRender.setScale(this.mScale);
			}

			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setScale, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}", this.getBasicInfoStr(), this.mScale.x, this.mScale.y, this.mScale.z), LogTypeId.eLogBeingMove);
			}
		}
	}

	void setSelfName(std::string name)
	{
		if (null != this.mRender)
		{
			if (!MacroDef.MOBILE_PLATFORM)
				this.mRender.setSelfName(name);
		}
	}

	// 自动管理
	virtual void autoHandle()
	{

	}

	// 初始化渲染器
	virtual void initRender()
	{

	}

	virtual void loadRenderRes()
	{

	}

	EntityRenderBase* getRender()
	{
		return this.mRender;
	}
}

MY_END_NAMESPACE