#include "MyProject.h"
#include "PlayerOtherRender.h"
#include "SceneEntityBase.h"
#include "UtilEngineWrap.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "EventDispatchDelegate.h"
#include "AuxScenePrefabLoader.h"
#include "Math/Vector.h"	// FVector
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
	if (nullptr == this->mAuxPrefabLoader)
	{
		//this->mAuxPrefabLoader = AssetStrIdBufferObjectFactory.newObject<AuxScenePrefabLoader>(this->mResPath, true);
		this->mAuxPrefabLoader = MY_NEW AuxScenePrefabLoader();
		//this->mAuxPrefabLoader.setEntityType(this->mEntity.getEntityType());
		this->mAuxPrefabLoader->setDestroySelf(true);
		this->mAuxPrefabLoader->setIsNeedInsRes(true);
		this->mAuxPrefabLoader->setIsInsNeedCoroutine(false);
		this->mAuxPrefabLoader->setIsInitOrientPos(true);
		this->mAuxPrefabLoader->setIsFakePos(true);
	}

	// 这种直接同步加载
	this->mAuxPrefabLoader->syncLoad(
		this->mResPath,
		MakeEventDispatchDelegate(
			this,
			&BeingEntityRender::onResLoaded, 
			(uint)0
		)
	);
}

void PlayerOtherRender::updateLocalTransform()
{
	if (nullptr != this->mSelfActor)
	{
		if (this->mIsPosDirty)
		{
			this->mIsPosDirty = false;

			FVector pos = this->mEntity->getPos();
			UtilEngineWrap::setPosByActor(this->mSelfActor, pos);
		}
	}
}

MY_END_NAMESPACE