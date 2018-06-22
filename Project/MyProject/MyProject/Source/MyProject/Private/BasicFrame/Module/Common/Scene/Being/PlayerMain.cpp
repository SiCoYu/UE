#include "MyProject.h"
#include "PlayerMain.h"
#include "PlayerMainMovement.h"
#include "PlayerMainAttack.h"
#include "PlayerMainRender.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "CtxExt.h"
#include "PlayerData.h"
#include "PlayerMgr.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerMain, Player)

PlayerMain::PlayerMain()
{
	this->mMovement = MY_NEW PlayerMainMovement(this);
	this->mAttack = MY_NEW PlayerMainAttack(this);
}

void PlayerMain::initRender()
{
	if (nullptr == this->mRender)
	{
		this->mRender = MY_NEW PlayerMainRender(this);
	}

	this->mRender->init();
}

void PlayerMain::_onPreInit()
{
	Super::_onPreInit();

	this->mMovement->init();
	this->mAttack->init();
}

void PlayerMain::_onPostInit()
{
	Super::_onPostInit();
}

void PlayerMain::dispose()
{
	if (nullptr != GPlayerMgr)
	{
		GPlayerMgr->removeHero();
	}

	Super::dispose();
}

void PlayerMain::putInPool()
{
	GPlayerMgr->removeHero();

	Super::putInPool();
}

void PlayerMain::onPutInPool()
{
	Super::onPutInPool();
}

void PlayerMain::autoHandle()
{
	Super::autoHandle();

	GPlayerMgr->addHero(this);
}

void PlayerMain::_onExecTick(float delta, TickMode tickMode)
{
	Super::_onExecTick(delta, tickMode);
}

void PlayerMain::_onPreTick(float delta, TickMode tickMode)
{
	Super::_onPreTick(delta, tickMode);
}

void PlayerMain::_onPostTick(float delta, TickMode tickMode)
{
	Super::_onPostTick(delta, tickMode);
}

MY_END_NAMESPACE