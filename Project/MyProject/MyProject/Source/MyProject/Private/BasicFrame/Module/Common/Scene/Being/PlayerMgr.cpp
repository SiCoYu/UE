#include "MyProject.h"
#include "PlayerMgr.h"
#include "PlayerMain.h"
#include "Player.h"
#include "TickMode.h"
#include "UtilMath.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerMgr, SceneEntityMgrBase)

PlayerMgr::PlayerMgr()
{
	this->mCurNum = 0;
	this->mMaxNum = 10;
}

void PlayerMgr::_onTickExec(float delta, TickMode tickMode)
{
	if (TickMode::eTM_Update == tickMode)
	{
		int idx = 0;
		int count = this->mSceneEntityList.count();
		SceneEntityBase* entity = nullptr;

		while (idx < count)
		{
			entity = this->mSceneEntityList[idx];

			if (!entity->isClientDispose())
			{
				entity->onTick(delta, tickMode);
			}

			++idx;
		}
	}
	else if(TickMode::eTM_LateUpdate == tickMode)
	{
		this->postUpdate();
	}
}

void PlayerMgr::postUpdate()
{
   
}

void PlayerMgr::initHero()
{
	PlayerMain* playerMain = this->createHero();
	this->addHero(playerMain);
	playerMain->init();
}

PlayerMain* PlayerMgr::createHero()
{
	return MY_NEW PlayerMain();
}

void PlayerMgr::addHero(PlayerMain* hero)
{
	if (nullptr != hero)
	{
		this->mHero = (PlayerMain*)hero;
		this->addPlayer(this->mHero);
	}
}

void PlayerMgr::removeHero()
{
	if (nullptr != this->mHero)
	{
		this->removePlayer(this->mHero);
		this->mHero = nullptr;
	}
}

PlayerMain* PlayerMgr::getHero()
{
	return this->mHero;
}

void PlayerMgr::init()
{
	Super::init();
}

void PlayerMgr::addPlayer(Player* player)
{
	this->addEntity(player);
}

void PlayerMgr::removePlayer(Player* player)
{
	this->removeEntity(player);
	--this->mMaxNum;
}

void PlayerMgr::createPlayerMain()
{
	this->mHero = MY_NEW PlayerMain();
	this->mHero->init();
	this->mHero->setDestPos(FVector(50, 1.3f, 50), true);
	this->mHero->setDestRotateEulerAngle(UtilMath::Euler(UtilMath::UnitQuat), true);
}

MY_END_NAMESPACE