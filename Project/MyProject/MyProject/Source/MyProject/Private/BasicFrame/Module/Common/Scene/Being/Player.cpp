#include "MyProject.h"
#include "Player.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(Player, BeingEntity)

Player::Player()
{

}

void Player::_onPreInit()
{
	Super::_onPreInit();
}

void Player::_onPostInit()
{
	Super::_onPostInit();
}

void Player::onDestroy()
{
	Super::onDestroy();
}

void Player::onPutInPool()
{
	Super::onPutInPool();
}

void Player::autoHandle()
{
	Super::autoHandle();
}

void Player::initRender()
{
	this->mRender = new PlayerRender(this);
	this->mRender.init();
}

MY_END_NAMESPACE