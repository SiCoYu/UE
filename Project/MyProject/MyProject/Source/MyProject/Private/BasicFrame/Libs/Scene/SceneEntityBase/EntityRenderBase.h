#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 基本的渲染器，所有与显示有关的接口都在这里，这里基本只提供接口，最基本的实现在 BeingEntityRender 里面
 */
public class EntityRenderBase : AuxComponent
{
protected:
	SceneEntityBase mEntity;  // Entity 数据
	protected EntityRenderCom mEntityRenderCom;

	private float totaltime;
	protected int mLayerDepth;  // Sprite 的深度值

	public EntityRenderBase(SceneEntityBase entity_)
	{
		this.mEntity = entity_;
		//this.mIsDestroySelf = false;
		this.mLayerDepth = (int)SceneLayerId.ePlayer;
	}

	virtual public void setClientDispose(bool isDispose)
	{

	}

	virtual public bool isClientDispose()
	{
		return this.mEntity.isClientDispose();
	}

	public EntityRenderCom getEntityCom()
	{
		return this.mEntityRenderCom;
	}

	virtual public void onTick(float delta, TickMode tickMode)
	{
		//if (null == this.mSpriteRender)
		if(null == this.mEntityRenderCom)
			return;
		if (this.mEntity.getEntityType() == EntityType.eFlyBullet || this.mEntity.getEntityType() == EntityType.eSnowBlock)
			return;

		bool IsGod = false;
		if(this.mEntity.getEntityType() == EntityType.ePlayerMainChild || this.mEntity.getEntityType() == EntityType.ePlayerOtherChild)
		{
			IsGod = (this.mEntity as PlayerChild).mParentPlayer.getIsGod();
			if (IsGod)// 无敌状态,0.1s闪烁一下
			{
				//totaltime += delta;
				//float remainder = totaltime % 0.2f;
				//this.mSpriteRender.enabled = remainder > 0.1f;

				this.mEntityRenderCom.mBeGodSpriteRender.enabled = true;
			}
			else
			{
				//this.mSpriteRender.enabled = true;
				this.mEntityRenderCom.mBeGodSpriteRender.enabled = false;
			}
		}
	}

	// 初始化流程
	override public void init()
	{
		this.onInit();
	}

	// 初始化事件，仅仅是变量初始化，初始化流程不修改
	virtual public void onInit()
	{
		this.setIsDestroySelf(false);
	}

	// 销毁流程
	override public void dispose()
	{
		if (null != this.mEntityRenderCom)
		{
			if (null != this.mEntityRenderCom.mBeGodSpriteRender)
			{
				this.mEntityRenderCom.mBeGodSpriteRender.enabled = false;
			}
			if (null != this.mEntityRenderCom.mFastTrailRender)
			{
				this.mEntityRenderCom.mFastTrailRender.enabled = false;
			}
			if (null != this.mEntityRenderCom.mNormalTrailRender)
			{
				this.mEntityRenderCom.mNormalTrailRender.enabled = false;
			}

			this.mEntityRenderCom = null;
		}

		base.dispose();
	}

	// 资源释放事件，仅仅是释放基本的资源，不修改销毁流程
	override public void onDestroy()
	{
		this.mEntity = null;

		base.onDestroy();
	}

	override public void putInPool()
	{
		base.putInPool();
	}

	override public void onPutInPool()
	{
		if(null != this.mEntityRenderCom)
		{
			if (null != this.mEntityRenderCom.mBeGodSpriteRender)
			{
				this.mEntityRenderCom.mBeGodSpriteRender.enabled = false;
			}
			if (null != this.mEntityRenderCom.mFastTrailRender)
			{
				this.mEntityRenderCom.mFastTrailRender.enabled = false;
			}
			if (null != this.mEntityRenderCom.mNormalTrailRender)
			{
				this.mEntityRenderCom.mNormalTrailRender.enabled = false;
			}

			this.mEntityRenderCom = null;
		}

		base.onPutInPool();
	}

	// 放到 Pool 中
	virtual protected void onResReturnToPool()
	{

	}

	virtual protected void onResGetFromPool()
	{
		UtilEngineWrap.SetActive(this.mSelfActor, true);
	}

	virtual public bool checkRender()
	{
		return false;
	}

	virtual public void load()
	{

	}

	// 场景对象不需要设置，因为如果设置了就检测不了隐藏显示了
	override public void show()
	{
		
	}

	override public void hide()
	{
		
	}

	// 强制显示
	public void forceShow()
	{
		base.show();
	}

	// 强制隐藏
	public void forceHide()
	{
		base.hide();
	}

	public bool isValid()
	{
		return null != this.mSelfActor;
	}

	virtual public void onClipShow()
	{

	}

	virtual public void onClipHide()
	{

	}

	public UnityEngine.Vector3 getPos()
	{
		if(this.isValid())
		{
			return this.transform().localPosition;
		}

		return UtilMath.ZeroVec3;
	}

	// 资源加载完成，初始化一些基本资源
	override protected void _onSelfChanged()
	{
		// 一定要先查找组件
		this.findCom();
		base._onSelfChanged();
		this.onResGetFromPool();

		// 设置可视化
		if (this.mEntity.IsVisible())
		{
			this.show();
		}
		else
		{
			this.hide();
		}

		// 设置方向位置信息
		this.setPos(this.mEntity.getPos());
		this.setRotate(this.mEntity.getRotate());
		this.setScale(this.mEntity.getScale());

		this.mEntity.onSelfActorChangedDispatch();
	}

	virtual protected void findCom()
	{

	}

	override public void updateLocalTransform()
	{
		if (this.mSelfActor)
		{
			if (this.mIsPosDirty)
			{
				this.mIsPosDirty = false;

				if (MacroDef.PHYSIX_MOVE && 
					(null != this.mEntityRenderCom.mRigidbody || null != this.mEntityRenderCom.mRigidbody2D))
				{
					//if (!(this.mEntity as BeingEntity).isFreezeXZ())
					//{
					UtilEngineWrap.setRigidbodyPos(this.mEntityRenderCom.mRigidbody, this.mEntity.getPos());
					UtilEngineWrap.setRigidbody2DPos(this.mEntityRenderCom.mRigidbody2D, this.mEntity.getPos());
					//}
					//else
					//{
					//    UtilEngineWrap.setPos(this.mSelfActor.transform, this.mEntity.getPos());
					//}
				}
				else
				{
					UtilEngineWrap.setPos(this.mSelfActor.transform, this.mEntity.getPos());
				}
			}
			if (this.mIsRotDirty)
			{
				this.mIsRotDirty = false;

				//if (null != this.mRigidbody)
				//{
				//    if (!(this.mEntity as BeingEntity).isFreezeXZ())
				//    {
				//        UtilEngineWrap.setRigidbodyRot(this.mRigidbody, this.mEntity.getRotate());
				//    }
				//    else
				//    {
				//        UtilEngineWrap.setRot(this.mSelfActor.transform, this.mEntity.getRotate());
				//    }
				//}
				//else
				//{
				//    UtilEngineWrap.setRot(this.mSelfActor.transform, this.mEntity.getRotate());
				//}

				UtilEngineWrap.setRot(this.mSelfActor.transform, this.mEntity.getRotate());
			}
			if (this.mIsScaleDirty)
			{
				this.mIsScaleDirty = false;

				//UtilEngineWrap.setScale(this.mSelfActor.transform, this.mEntity.getScale());
			}
		}
	}

	virtual public void setTexture(string path)
	{

	}

	virtual public void setTexTile(TileInfo tileInfo)
	{

	}

	virtual public void enableRigid(bool enable)
	{

	}

	virtual public void attachToParentNode(EntityRenderBase render)
	{

	}

	public UnityEngine.GameObject getEffectSocket()
	{
		UnityEngine.GameObject go = null;
		go = UtilEngineWrap.TransFindChildByPObjAndPath(this.mSelfActor, "TopEffect");
		return go;
	}

	public int getSortingOrder()
	{
		return this.mLayerDepth;
	}

	public void setSortingOrder(int order)
	{
		this.mLayerDepth = order;
	}

	virtual public void updateArrowDirectionScale()
	{

	}
}