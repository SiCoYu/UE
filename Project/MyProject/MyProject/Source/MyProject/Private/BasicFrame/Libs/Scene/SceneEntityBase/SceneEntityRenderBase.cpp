#include "MyProject.h"
#include "SceneEntityRenderBase.h"
#include "SceneEntityBase.h"
#include "AuxComponent.h"
#include "UtilMath::h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityRenderBase, AuxComponent)

SceneEntityRenderBase::SceneEntityRenderBase(SceneEntityBase* entity_)
{
	this->mEntity = entity_;
}

void SceneEntityRenderBase::setClientDispose(bool isDispose)
{

}

bool SceneEntityRenderBase::isClientDispose()
{
	return this->mEntity->isClientDispose();
}

void SceneEntityRenderBase::onTick(float delta, TickMode tickMode)
{
	
}

// 初始化流程
void SceneEntityRenderBase::init()
{
	this->onInit();
}

// 初始化事件，仅仅是变量初始化，初始化流程不修改
void SceneEntityRenderBase::onInit()
{
	this->setIsDestroySelf(false);
}

// 销毁流程
void SceneEntityRenderBase::dispose()
{
	Super::dispose();
}

// 资源释放事件，仅仅是释放基本的资源，不修改销毁流程
void SceneEntityRenderBase::onDestroy()
{
	this->mEntity = nullptr;

	Super::onDestroy();
}

bool SceneEntityRenderBase::checkRender()
{
	return false;
}

void SceneEntityRenderBase::load()
{

}

// 场景对象不需要设置，因为如果设置了就检测不了隐藏显示了
void SceneEntityRenderBase::show()
{
	
}

void SceneEntityRenderBase::hide()
{
	
}

bool SceneEntityRenderBase::isValid()
{
	return nullptr != this->mSelfActor;
}

FVector SceneEntityRenderBase::getPos()
{
	if(this->isValid())
	{
		//return this->transform().localPosition;
	}

	return UtilMath::ZeroVec3;
}

void SceneEntityRenderBase::setScale(FVector value)
{

}

// 资源加载完成，初始化一些基本资源
void SceneEntityRenderBase::_onSelfChanged()
{
	// 一定要先查找组件
	Super::_onSelfChanged();

	// 设置可视化
	if (this->mEntity->IsVisible())
	{
		this->show();
	}
	else
	{
		this->hide();
	}

	// 设置方向位置信息
	this->setPos(this->mEntity->getPos());
	this->setRotate(this->mEntity->getRotate());
	this->setScale(this->mEntity->getScale());
}

void SceneEntityRenderBase::updateLocalTransform()
{
	if (this->mSelfActor)
	{
		if (this->mIsPosDirty)
		{
			this->mIsPosDirty = false;

			//UtilEngineWrap::setPos(this->mSelfActor.transform, this->mEntity.getPos());
		}
		if (this->mIsRotDirty)
		{
			this->mIsRotDirty = false;

			//if (nullptr != this->mRigidbody)
			//{
			//    if (!(this->mEntity as BeingEntity).isFreezeXZ())
			//    {
			//        UtilEngineWrap::setRigidbodyRot(this->mRigidbody, this->mEntity.getRotate());
			//    }
			//    else
			//    {
			//        UtilEngineWrap::setRot(this->mSelfActor.transform, this->mEntity.getRotate());
			//    }
			//}
			//else
			//{
			//    UtilEngineWrap::setRot(this->mSelfActor.transform, this->mEntity.getRotate());
			//}

			//UtilEngineWrap::setRot(this->mSelfActor.transform, this->mEntity.getRotate());
		}
		if (this->mIsScaleDirty)
		{
			this->mIsScaleDirty = false;

			//UtilEngineWrap::setScale(this->mSelfActor.transform, this->mEntity.getScale());
		}
	}
}

void SceneEntityRenderBase::setTexture(std::string path)
{

}

MY_END_NAMESPACE