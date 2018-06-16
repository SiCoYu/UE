#include "MyProject.h"
#include "PlayerMain.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMain::PlayerMain()
{
	this.mMovement = new PlayerMainMovement(this);
	this.mAttack = new PlayerMainAttack(this);
}

void PlayerMain::initRender()
{
	if (null == this.mRender)
	{
		this.mRender = new PlayerMainRender(this);
	}

	this.mRender.init();
}

void PlayerMain::_onPreInit()
{
	base._onPreInit();

	this.mMovement.init();
	this.mAttack.init();
}

void PlayerMain::_onPostInit()
{
	base._onPostInit();
}

void PlayerMain::dispose()
{
	if (null != Ctx.msInstance.mPlayerMgr)
	{
		Ctx.msInstance.mPlayerMgr.removeHero();
	}

	base.dispose();
}

void PlayerMain::putInPool()
{
	Ctx.msInstance.mPlayerMgr.removeHero();

	base.putInPool();
}

void PlayerMain::onPutInPool()
{
	base.onPutInPool();
}

void PlayerMain::autoHandle()
{
	base.autoHandle();

	Ctx.msInstance.mPlayerMgr.addHero(this);
}

void PlayerMain::_onExecTick(float delta, TickMode tickMode)
{
	base._onExecTick(delta, tickMode);
}

void PlayerMain::_onPreTick(float delta, TickMode tickMode)
{
	base._onPreTick(delta, tickMode);
}

void PlayerMain::_onPostTick(float delta, TickMode tickMode)
{
	base._onPostTick(delta, tickMode);
}

MY_END_NAMESPACE