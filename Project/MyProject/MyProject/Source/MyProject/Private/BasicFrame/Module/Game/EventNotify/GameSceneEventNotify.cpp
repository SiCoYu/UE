#include "MyProject.h"
#include "GameSceneEventNotify.h"
#include "Prequisites.h"
#include "UiFunctionBar.h"
#include "UiFormId.h"

#ifdef ENABLE_UNIT_TEST
	#include "TestMain.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

GameSceneEventNotify::GameSceneEventNotify()
{
	
}

GameSceneEventNotify::~GameSceneEventNotify()
{
	
}

// 场景加载完成处理事件
void GameSceneEventNotify::onLevelLoaded()
{
	GUiMgr->loadAndShow<UUiFunctionBar>(UiFormId::eUiFunctionBar);

    this->runTest();
}

void GameSceneEventNotify::init()
{

}

void GameSceneEventNotify::dispose()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain->dispose();
	this->mTestMain.setNull();
#endif
}

void GameSceneEventNotify::runTest()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain = MySharedPtr<TestMain>(MY_NEW TestMain());
	this->mTestMain->runTest();
#endif
}

MY_END_NAMESPACE