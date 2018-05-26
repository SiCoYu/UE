#include "MyProject.h"
#include "GameSceneEventNotify.h"
#include "Prequisites.h"
#include "UiFunctionBar.h"
#include "UiFormId.h"

#ifdef ENABLE_UNIT_TEST
	#include "TestMain.h"
#endif

GameSceneEventNotify::GameSceneEventNotify()
{
	
}

GameSceneEventNotify::~GameSceneEventNotify()
{
	
}

// 场景加载完成处理事件
void GameSceneEventNotify::onLevelLoaded()
{
	GUiMgr->loadAndShow<UUiFunctionBar>(NSFormId::eUiFunctionBar);

    this->runTest();
}

void GameSceneEventNotify::init()
{

}

void GameSceneEventNotify::dispose()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain->dispose();
#endif

#ifdef ENABLE_UNIT_TEST
	this->mTestMain.setNull();
#endif
}

void GameSceneEventNotify::runTest()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain = MySharedPtr<TestMain>(new TestMain());
	this->mTestMain->runTest();
#endif
}