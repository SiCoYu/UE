#include "MyProject.h"
#include "BeingEntityRender.h"
#include "SceneEntityBase.h"
#include "IDispatchObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(BeingEntityRender, SceneEntityRenderBase)

BeingEntityRender::BeingEntityRender(SceneEntityBase* entity_)
	: Super(entity_)
{

}

void BeingEntityRender::setResPath(std::string path)
{
	this->mResPath = path;
}

virtual void onDestroy() override
{
	this->releaseRes();

	Super::onDestroy();
}

virtual void onPutInPool() override
{
	this->releaseRes();

	Super::onPutInPool();
}

protected:
	// 仅仅是释放资源
	virtual void releaseRes()
	{

	}

public:
	override void updateLocalTransform()
	{
		if (this->mSelfActor)
		{
			if (this->mIsPosDirty)
			{
				this->mIsPosDirty = false;

				// 只有自己才是物理移动
				if (MacroDef.PHYSIX_MOVE &&
					(nullptr != this->mEntityRenderCom.mRigidbody || this->mEntityRenderCom.mRigidbody2D) && EntityType.ePlayerMainChild == this->mEntity.getEntityType())
				{
					UtilEngineWrap.setRigidbodyPos(this->mEntityRenderCom.mRigidbody, this->mEntity.getPos());
					UtilEngineWrap.setRigidbody2DPos(this->mEntityRenderCom.mRigidbody2D, this->mEntity.getPos());
				}
				else
				{
					UtilEngineWrap.setPos(this->mSelfActor.transform, this->mEntity.getPos());
				}
				// 内部 2D 物理组件总是会移动，因此重置一下
				UtilEngineWrap.resetRST(this->mEntityRenderCom.mColliderTrans);
			}
			if (this->mIsRotDirty)
			{
				this->mIsRotDirty = false;

				UtilEngineWrap.setRot(this->mSelfActor.transform, this->mEntity.getRotate());
			}
			if (this->mIsScaleDirty)
			{
				this->mIsScaleDirty = false;

				//UtilEngineWrap.setScale(this->mSelfActor.transform, this->mEntity.getScale());
			}
		}
	}

	// 资源加载
	override void load()
	{
		if (nullptr == this->mAuxPrefabLoader)
		{
			this->mAuxPrefabLoader = AssetStrIdBufferObjectFactory.newObject<AuxScenePrefabLoader>(this->mResPath, true);
			this->mAuxPrefabLoader.setEntityType(this->mEntity.getEntityType());
			this->mAuxPrefabLoader.setDestroySelf(true);
			this->mAuxPrefabLoader.setIsNeedInsRes(true);
			this->mAuxPrefabLoader.setIsInsNeedCoroutine(true);
			this->mAuxPrefabLoader.setIsInitOrientPos(true);
			this->mAuxPrefabLoader.setIsFakePos(true);
		}

		this->mAuxPrefabLoader.asyncLoad(this->mResPath, nullptr, this->onResLoaded);
	}

	virtual void onResLoaded(IDispatchObject* dispObj, uint uniqueId)
	{
		this->setSelfActor(this->mAuxPrefabLoader.getGameObject());
	}

protected:
	virtual void _onSelfChanged() override
	{
		Super::_onSelfChanged();
	}

MY_END_NAMESPACE