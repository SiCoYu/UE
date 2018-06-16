#include "MyProject.h"
#include "Player.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

Player::Player()
{

}

void Player::_onPreInit()
{
	base._onPreInit();
}

void Player::_onPostInit()
{
	base._onPostInit();
}

void Player::onDestroy()
{
	base.onDestroy();
}

void Player::onPutInPool()
{
	base.onPutInPool();
}

void Player::autoHandle()
{
	base.autoHandle();
}

void Player::initRender()
{
	this.mRender = new PlayerRender(this);
	this.mRender.init();
}

MY_END_NAMESPACE