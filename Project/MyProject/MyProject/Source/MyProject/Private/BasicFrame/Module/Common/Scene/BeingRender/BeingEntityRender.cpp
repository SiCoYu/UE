#include "MyProject.h"
#include "BeingEntityRender.h"
#include "SceneEntityBase.h"
#include "SceneEntityRenderBase.h"
#include "IDispatchObject.h"
#include "UtilEngineWrap.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "EventDispatchDelegate.h"
#include "AuxScenePrefabLoader.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(BeingEntityRender, SceneEntityRenderBase)

BeingEntityRender::BeingEntityRender(SceneEntityBase* entity_)
	: Super(entity_)
{
	this->mAuxPrefabLoader = nullptr;
}

void BeingEntityRender::setResPath(std::string path)
{
	this->mResPath = path;
}

void BeingEntityRender::onDestroy()
{
	this->releaseRes();

	Super::onDestroy();
}

void BeingEntityRender::onPutInPool()
{
	this->releaseRes();

	Super::onPutInPool();
}

// 仅仅是释放资源
void BeingEntityRender::releaseRes()
{

}

void BeingEntityRender::attachToParentNode(SceneEntityRenderBase* render)
{

}

void BeingEntityRender::updateLocalTransform()
{
	if (this->mSelfActor)
	{
		if (this->mIsPosDirty)
		{
			this->mIsPosDirty = false;

			UtilEngineWrap::setPosByActor(this->mSelfActor, this->mEntity->getPos());
		}
		if (this->mIsRotDirty)
		{
			this->mIsRotDirty = false;

			UtilEngineWrap::setRotateByActor(this->mSelfActor, this->mEntity->getRotate());
		}
		if (this->mIsScaleDirty)
		{
			this->mIsScaleDirty = false;

			UtilEngineWrap::setScaleByActor(this->mSelfActor, this->mEntity->getScale());
		}
	}
}

// 资源加载
void BeingEntityRender::load()
{
	if (nullptr == this->mAuxPrefabLoader)
	{
		//this->mAuxPrefabLoader = AssetStrIdBufferObjectFactory.newObject<AuxScenePrefabLoader>(this->mResPath, true);
		this->mAuxPrefabLoader = MY_NEW AuxScenePrefabLoader(
			this->mResPath,
			true, 
			true
		);
		//this->mAuxPrefabLoader->setEntityType(this->mEntity.getEntityType());
		this->mAuxPrefabLoader->setDestroySelf(true);
		this->mAuxPrefabLoader->setIsNeedInsRes(true);
		this->mAuxPrefabLoader->setIsInsNeedCoroutine(true);
		this->mAuxPrefabLoader->setIsInitOrientPos(true);
		this->mAuxPrefabLoader->setIsFakePos(true);
	}

	this->mAuxPrefabLoader->asyncLoad(
		this->mResPath, 
		MakeEventDispatchDelegate(this, this->onResLoaded)
	);
}

void BeingEntityRender::onResLoaded(IDispatchObject* dispObj/*, uint uniqueId*/)
{
	this->setSelfActor(this->mAuxPrefabLoader->getActor());
}

void BeingEntityRender::_onSelfChanged()
{
	Super::_onSelfChanged();
}

MY_END_NAMESPACE