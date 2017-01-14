#include "MyProject.h"
#include "GameSceneEventCB.h"

// 场景加载完成处理事件
void GameSceneEventCB::onLevelLoaded()
{
    Ctx.mInstance.mUiMgr.loadAndShow(UIFormId.eUIPack);
    this->runTest();
}

void GameSceneEventCB::runTest()
{

}

void GameSceneEventCB::init()
{

}