#include "MyProject.h"
#include "GameSceneEventCB.h"
#include "Common.h"

#ifdef ENABLE_UNIT_TEST
	#include "TestMain.h"
#endif

// 场景加载完成处理事件
void GameSceneEventCB::onLevelLoaded()
{
	GUiMgr->loadAndShow<UUIFunctionBar>(NSFormId::eUIFunctionBar);
    //this->runTest();
}

void GameSceneEventCB::init()
{

}

void GameSceneEventCB::dispose()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain->dispose();
#endif

#ifdef ENABLE_UNIT_TEST
	this->mTestMain = nullptr;
#endif
}

void GameSceneEventCB::runTest()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain = MySharedPtr<TestMain>(new TestMain());
	this->mTestMain->runTest();
#endif
}

void GameSceneEventCB::init()
{

}