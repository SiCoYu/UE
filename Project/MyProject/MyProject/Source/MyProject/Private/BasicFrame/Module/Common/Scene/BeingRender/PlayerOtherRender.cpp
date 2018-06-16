#include "MyProject.h"
#include "PlayerOtherRender.h"
#include "SceneEntityBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerOtherRender, PlayerRender)

PlayerOtherRender::PlayerOtherRender(SceneEntityBase* entity_)
		: Super(entity_)
{

}

void PlayerOtherRender::onInit()
{
	Super::onInit();
}

// 资源加载
void PlayerOtherRender::load()
{
	//if (nullptr == this->mAuxPrefabLoader)
	//{
	//	this->mAuxPrefabLoader = AssetStrIdBufferObjectFactory.newObject<AuxScenePrefabLoader>(this->mResPath, true);
	//	this->mAuxPrefabLoader.setEntityType(this->mEntity.getEntityType());
	//	this->mAuxPrefabLoader.setDestroySelf(true);
	//	this->mAuxPrefabLoader.setIsNeedInsRes(true);
	//	this->mAuxPrefabLoader.setIsInsNeedCoroutine(false);
	//	this->mAuxPrefabLoader.setIsInitOrientPos(true);
	//	this->mAuxPrefabLoader.setIsFakePos(true);
	//}

	//// 这种直接同步加载
	//this->mAuxPrefabLoader.syncLoad(
	//	this->mResPath,
	//	nullptr, 
	//	this->onResLoaded
	//);
}

void PlayerOtherRender::updateLocalTransform()
{
	if (nullptr != this->mSelfActor)
	{
		if (this->mIsPosDirty)
		{
			this->mIsPosDirty = false;

			//UtilEngineWrap::setPos(this->mSelfActor.transform, this->mEntity.getPos());
		}
	}
}

MY_END_NAMESPACE