#include "MyProject.h"
#include "PlayerMain.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMain::PlayerMain()
{
	this->mMovement = new PlayerMainMovement(this);
	this->mAttack = new PlayerMainAttack(this);
}

void PlayerMain::initRender()
{
	if (nullptr == this->mRender)
	{
		this->mRender = new PlayerMainRender(this);
	}

	this->mRender.init();
}

void PlayerMain::_onPreInit()
{
	Super::_onPreInit();

	this->mMovement.init();
	this->mAttack.init();
}

void PlayerMain::_onPostInit()
{
	Super::_onPostInit();
}

void PlayerMain::dispose()
{
	if (nullptr != Ctx.msInstance.mPlayerMgr)
	{
		Ctx.msInstance.mPlayerMgr.removeHero();
	}

	Super::dispose();
}

void PlayerMain::putInPool()
{
	Ctx.msInstance.mPlayerMgr.removeHero();

	Super::putInPool();
}

void PlayerMain::onPutInPool()
{
	Super::onPutInPool();
}

void PlayerMain::autoHandle()
{
	Super::autoHandle();

	Ctx.msInstance.mPlayerMgr.addHero(this);
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