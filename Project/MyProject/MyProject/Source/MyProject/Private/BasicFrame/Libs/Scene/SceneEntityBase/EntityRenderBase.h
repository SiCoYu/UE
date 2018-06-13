#pragma once

#include <string>
#include "GObject.h"
#include "AuxComponent.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

/**
 * @brief 基本的渲染器，所有与显示有关的接口都在这里，这里基本只提供接口，最基本的实现在 BeingEntityRender 里面
 */
class EntityRenderBase : public AuxComponent
{
	M_DECLARE_CLASS(EntityRenderBase, AuxComponent)

protected:
	SceneEntityBase* mEntity;  // Entity 数据

public:
	EntityRenderBase(SceneEntityBase* entity_)
	{
		this->mEntity = entity_;
	}

	virtual void setClientDispose(bool isDispose)
	{

	}

	virtual bool isClientDispose()
	{
		return this->mEntity.isClientDispose();
	}

	virtual void onTick(float delta, TickMode tickMode)
	{
		
	}

	// 初始化流程
	override void init()
	{
		this->onInit();
	}

	// 初始化事件，仅仅是变量初始化，初始化流程不修改
	virtual void onInit()
	{
		this->setIsDestroySelf(false);
	}

	// 销毁流程
	override void dispose()
	{
		Super::dispose();
	}

	// 资源释放事件，仅仅是释放基本的资源，不修改销毁流程
	override void onDestroy()
	{
		this->mEntity = nullptr;

		Super::onDestroy();
	}

	virtual bool checkRender()
	{
		return false;
	}

	virtual void load()
	{

	}

	// 场景对象不需要设置，因为如果设置了就检测不了隐藏显示了
	override void show()
	{
		
	}

	override void hide()
	{
		
	}

	bool isValid()
	{
		return nullptr != this->mSelfActor;
	}

	FVector getPos()
	{
		if(this->isValid())
		{
			return this->transform().localPosition;
		}

		return UtilMath.ZeroVec3;
	}

	// 资源加载完成，初始化一些基本资源
	virtual void _onSelfChanged() override
	{
		// 一定要先查找组件
		Super::_onSelfChanged();

		// 设置可视化
		if (this->mEntity.IsVisible())
		{
			this->show();
		}
		else
		{
			this->hide();
		}

		// 设置方向位置信息
		this->setPos(this->mEntity.getPos());
		this->setRotate(this->mEntity.getRotate());
		this->setScale(this->mEntity.getScale());
	}
	
	virtual void updateLocalTransform() override
	{
		if (this->mSelfActor)
		{
			if (this->mIsPosDirty)
			{
				this->mIsPosDirty = false;

				UtilEngineWrap.setPos(this->mSelfActor.transform, this->mEntity.getPos());
			}
			if (this->mIsRotDirty)
			{
				this->mIsRotDirty = false;

				//if (nullptr != this->mRigidbody)
				//{
				//    if (!(this->mEntity as BeingEntity).isFreezeXZ())
				//    {
				//        UtilEngineWrap.setRigidbodyRot(this->mRigidbody, this->mEntity.getRotate());
				//    }
				//    else
				//    {
				//        UtilEngineWrap.setRot(this->mSelfActor.transform, this->mEntity.getRotate());
				//    }
				//}
				//else
				//{
				//    UtilEngineWrap.setRot(this->mSelfActor.transform, this->mEntity.getRotate());
				//}

				UtilEngineWrap.setRot(this->mSelfActor.transform, this->mEntity.getRotate());
			}
			if (this->mIsScaleDirty)
			{
				this->mIsScaleDirty = false;

				//UtilEngineWrap.setScale(this->mSelfActor.transform, this->mEntity.getScale());
			}
		}
	}

	virtual void setTexture(std::string path)
	{

	}
}