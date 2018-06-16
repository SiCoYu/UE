#include "MyProject.h"
#include "PlayerMainRender.h"
#include "SceneEntityBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerMainRender, PlayerRender)

PlayerMainRender::PlayerMainRender(SceneEntityBase* entity_)
	: Super(entity_)
{

}

void PlayerMainRender::onInit()
{
	Super::onInit();
}

void PlayerMainRender::_onSelfChanged()
{
	Super::_onSelfChanged();
}

void PlayerMainRender::show()
{
	if (!IsVisible())
	{
		UtilEngineWrap::SetActive(this->mSelfActor, true);
	}
}

void PlayerMainRender::hide()
{
	if (this->IsVisible())
	{
		UtilEngineWrap::SetActive(this->mSelfActor, false);
	}
}

// 资源加载
void PlayerMainRender::load()
{
	if (nullptr == this->mAuxPrefabLoader)
	{
		this->mAuxPrefabLoader = AssetStrIdBufferObjectFactory.newObject<AuxScenePrefabLoader>(this->mResPath, true);
		this->mAuxPrefabLoader.setEntityType(this->mEntity.getEntityType());
		this->mAuxPrefabLoader.setDestroySelf(true);
		this->mAuxPrefabLoader.setIsNeedInsRes(true);
		this->mAuxPrefabLoader.setIsInsNeedCoroutine(false);
		this->mAuxPrefabLoader.setIsInitOrientPos(true);
		this->mAuxPrefabLoader.setIsFakePos(true);
	}

	// 这种直接同步加载
	this->mAuxPrefabLoader.syncLoad(
		this->mResPath,
		nullptr,
		this->onResLoaded
	);
}

void PlayerMainRender::updateLocalTransform()
{
	if (nullptr != this->mSelfActor)
	{
		if (this->mIsPosDirty)
		{
			this->mIsPosDirty = false;

			UtilEngineWrap::setPos(this->mSelfActor.transform, this->mEntity.getPos());
		}
	}
}

MY_END_NAMESPACE