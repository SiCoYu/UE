#include "MyProject.h"
#include "EntityRenderBase.h"

MY_BEGIN_NAMESPACE(MyNS)

EntityRenderBase::EntityRenderBase(SceneEntityBase* entity_)
{
	this.mEntity = entity_;
}

void EntityRenderBase::setClientDispose(bool isDispose)
{

}

bool EntityRenderBase::isClientDispose()
{
	return this.mEntity.isClientDispose();
}

void EntityRenderBase::onTick(float delta, TickMode tickMode)
{
	
}

// 初始化流程
void EntityRenderBase::init()
{
	this.onInit();
}

// 初始化事件，仅仅是变量初始化，初始化流程不修改
void EntityRenderBase::onInit()
{
	this.setIsDestroySelf(false);
}

// 销毁流程
void EntityRenderBase::dispose()
{
	base.dispose();
}

// 资源释放事件，仅仅是释放基本的资源，不修改销毁流程
void EntityRenderBase::onDestroy()
{
	this.mEntity = null;

	base.onDestroy();
}

bool EntityRenderBase::checkRender()
{
	return false;
}

void EntityRenderBase::load()
{

}

// 场景对象不需要设置，因为如果设置了就检测不了隐藏显示了
void EntityRenderBase::show()
{
	
}

void EntityRenderBase::hide()
{
	
}

bool EntityRenderBase::isValid()
{
	return null != this.mSelfActor;
}

UnityEngine.Vector3 EntityRenderBase::getPos()
{
	if(this.isValid())
	{
		return this.transform().localPosition;
	}

	return UtilMath.ZeroVec3;
}

// 资源加载完成，初始化一些基本资源
void EntityRenderBase::_onSelfChanged() override
{
	// 一定要先查找组件
	base._onSelfChanged();

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
}

void EntityRenderBase::updateLocalTransform() override
{
	if (this.mSelfActor)
	{
		if (this.mIsPosDirty)
		{
			this.mIsPosDirty = false;

			UtilEngineWrap.setPos(this.mSelfActor.transform, this.mEntity.getPos());
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

void EntityRenderBase::setTexture(std::string path)
{

}

MY_END_NAMESPACE