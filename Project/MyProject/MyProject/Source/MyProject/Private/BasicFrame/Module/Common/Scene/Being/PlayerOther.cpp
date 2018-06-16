#include "MyProject.h"
#include "PlayerOther.h"
#include "PlayerOtherMovement.h"
#include "PlayerOtherAttack.h"
#include "PlayerOtherRender.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerOther, Player)

PlayerOther::PlayerOther()
{
	this->mMovement = MY_NEW PlayerOtherMovement(this);
	this->mAttack = MY_NEW PlayerOtherAttack(this);
}

void PlayerOther::_onPostInit()
{
	Super::_onPostInit();

	//this->hide();

	this->mMovement.init();
	this->mAttack.init();
}

void PlayerOther::initRender()
{
	if (nullptr == this->mRender)
	{
		this->mRender = MY_NEW PlayerOtherRender(this);
	}

	this->mRender->init();
}

void PlayerOther::dispose()
{
	if (nullptr != GPlayerMgr)
	{
		GPlayerMgr->removePlayer(this);
	}

	Super::dispose();
}

void PlayerOther::putInPool()
{
	GPlayerMgr->removePlayer(this);

	Super::putInPool();
}

void PlayerOther::onPutInPool()
{
	Super::onPutInPool();
}

void PlayerOther::autoHandle()
{
	Super::autoHandle();

	GPlayerMgr->addPlayer(this);
}

void PlayerOther::setPos(FVector pos)
{
	Super::setPos(pos);

	// 如果 Hero ，没有移动的时候，才更新，如果 Hero 在移动，直接通过相机移动更新
	//if (!GPlayerMgr->isHeroMoving())
	//{
	//	if (nullptr != this->mHud)
	//	{
	//		this->mHud.onPosChanged();
	//	}
	//}
}

MY_END_NAMESPACE