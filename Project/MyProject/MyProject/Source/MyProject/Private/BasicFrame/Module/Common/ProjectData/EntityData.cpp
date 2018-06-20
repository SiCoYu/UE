#include "MyProject.h"
#include "EntityData.h"
#include "PlayerMgr.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerData, GObject)

EntityData::EntityData()
{
	this->mPlayerMgr = MySharedPtr<PlayerMgr>(MY_NEW PlayerMgr());
}

void EntityData::init()
{
	this->mPlayerMgr->init();
}

void EntityData::dispose()
{
	this->mPlayerMgr->dispose();

	this->mPlayerMgr.setNull();
}

MySharedPtr<PlayerMgr> EntityData::getPlayerMgr()
{
	return this->mPlayerMgr;
}

void EntityData::setPlayerMgr(MySharedPtr<PlayerMgr>& value)
{
	this->mPlayerMgr = value;
}

MY_END_NAMESPACE