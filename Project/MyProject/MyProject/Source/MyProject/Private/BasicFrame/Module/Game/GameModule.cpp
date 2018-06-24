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

MY_BEGIN_NAMESPACE(MyNS)

GameModule::GameModule()
{

}

void GameModule::init()
{
	this->initGVar();
	this->loadGameScene();
}

void GameModule::dispose()
{
	MY_SAFE_DISPOSE(this->mGameNetNotify);
	MY_SAFE_DISPOSE(this->mGameRouteNotify);
	//if (nullptr != this->mGotoScene)
	//{
	//    this->mGotoScene.dispose();
	//    this->mGotoScene = nullptr;
	//}
	MY_SAFE_DISPOSE(this->mGameUiEventNotify);
	MY_SAFE_DISPOSE(this->mGameSceneEventNotify);
	MY_SAFE_DISPOSE(this->mGameSceneInputNotify);
}

void GameModule::initGVar()
{
	//this->mGotoScene = new GotoScene();

	this->mGameNetNotify = MY_NEW GameNetNotify();
	this->mGameNetNotify.init();
	Ctx.msInstance.mNetCmdNotify.addOneNofity(this->mGameNetNotify);

	this->mGameRouteNotify = MY_NEW GameRouteNotify();
	this->mGameRouteNotify.init();
	Ctx.msInstance.mMsgRouteNotify.addOneNotify(this->mGameRouteNotify);

	this->mGameSceneEventNotify = MY_NEW GameSceneEventNotify();
	this->mGameScenInputNotify = MY_NEW GameSceneInputNotify();

	//this->mGotoScene.init();
	//this->mGotoScene.addSceneHandle();
}

void GameModule::loadGameScene()
{
	//if (MacroDef.DISABLE_TEST_SCENE)
	//{
	//    this->mGotoScene.loadSceneByMapId((int)MapIdCV.eCommonMap);
	//}
	//else
	//{
	//    this->mGotoScene.loadSceneByLevelName("TestShader.unity");
	//}
}

MY_END_NAMESPACE