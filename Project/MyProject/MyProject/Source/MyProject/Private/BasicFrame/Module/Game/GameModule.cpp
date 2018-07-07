#include "MyProject.h"
#include "GameModule.h"
#include "GameRouteNotify.h"
#include "GameNetNotify.h"
#include "GameUiEventNotify.h"
#include "GameSceneEventNotify.h"
#include "GameSceneInputNotify.h"
#include "SafePointer.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "CtxExt.h"
#include "EntityData.h"
#include "PlayerMgr.h"
#include "PlayerMain.h"
#include "SceneNavigation.h"
#include "GameEventCmd.h"

MY_BEGIN_NAMESPACE(MyNS)

GameModule::GameModule()
{
	this->mGameNetNotify = nullptr;
	this->mGameRouteNotify = nullptr;
	this->mGameUiEventNotify = nullptr;
	this->mGameSceneEventNotify = nullptr;
	this->mGameSceneInputNotify = nullptr;
	this->mGameEventCmd = nullptr;
}

void GameModule::init()
{
	this->initGVar();
	this->loadGameScene();
	this->mGameSceneEventNotify->onLevelLoaded();

	GPlayerMgr->initHero();
}

void GameModule::dispose()
{
	MY_SAFE_DISPOSE(this->mGameNetNotify);
	MY_SAFE_DISPOSE(this->mGameRouteNotify);
	MY_SAFE_DISPOSE(this->mGameUiEventNotify);
	MY_SAFE_DISPOSE(this->mGameSceneEventNotify);
	MY_SAFE_DISPOSE(this->mGameSceneInputNotify);
	MY_SAFE_DISPOSE(this->mGameEventCmd);
}

void GameModule::initGVar()
{
	this->mGameNetNotify = MY_NEW GameNetNotify();
	this->mGameNetNotify->init();

	this->mGameRouteNotify = MY_NEW GameRouteNotify();
	this->mGameRouteNotify->init();

	this->mGameUiEventNotify = MY_NEW GameUiEventNotify();
	this->mGameUiEventNotify->init();

	this->mGameSceneEventNotify = MY_NEW GameSceneEventNotify();
	this->mGameSceneEventNotify->init();

	this->mGameSceneInputNotify = MY_NEW GameSceneInputNotify();
	this->mGameSceneInputNotify->init();

	this->mGameEventCmd = MY_NEW GameEventCmd();
	this->mGameEventCmd->init();
}

void GameModule::loadGameScene()
{
	//if (MacroDef.DISABLE_TEST_SCENE)
	//{
	//    GSceneNavigation->loadSceneByMapId((int)MapIdCV.eCommonMap);
	//}
	//else
	//{
	//    GSceneNavigation->loadSceneByLevelName("TestShader.unity");
	//}
}

MY_END_NAMESPACE