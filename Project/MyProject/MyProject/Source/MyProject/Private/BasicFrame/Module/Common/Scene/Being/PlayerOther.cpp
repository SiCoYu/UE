#include "MyProject.h"
#include "PlayerOther.h"
#include "PlayerOtherMovement.h"
#include "PlayerOtherAttack.h"
#include "PlayerOtherRender.h"
#include "PlayerOther.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerOther::PlayerOther()
{
	this->mMovement = new PlayerOtherMovement(this);
	this->mAttack = new PlayerOtherAttack(this);
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
		this->mRender = new PlayerOtherRender(this);
	}

	this->mRender.init();
}

void PlayerOther::dispose()
{
	if (nullptr != Ctx.msInstance.mPlayerMgr)
	{
		Ctx.msInstance.mPlayerMgr.removePlayer(this);
	}

	Super::dispose();
}

void PlayerOther::putInPool()
{
	Ctx.msInstance.mPlayerMgr.removePlayer(this);

	Super::putInPool();
}

void PlayerOther::onPutInPool()
{
	if(nullptr != Ctx.msInstance.mBeginnerGuideSys && 
	   Ctx.msInstance.mBeginnerGuideSys.isEnableGuide())
	{
		Ctx.msInstance.mBeginnerGuideSys.beatOneEnemy();
	}

	Super::onPutInPool();
}

void PlayerOther::autoHandle()
{
	Super::autoHandle();

	Ctx.msInstance.mPlayerMgr.addPlayer(this);
}

void PlayerOther::setPos(FVector pos)
{
	Super::setPos(pos);
	// 如果 Hero ，没有移动的时候，才更新，如果 Hero 在移动，直接通过相机移动更新
	//if (!Ctx.msInstance.mPlayerMgr.isHeroMoving())
	{
		if (nullptr != this->mHud)
		{
			this->mHud.onPosChanged();
		}
	}
}

MY_END_NAMESPACE