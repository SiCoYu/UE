#pragma once

#include "ISceneEventCB.h"
#include "MySharedPointer.h"

#ifdef ENABLE_UNIT_TEST
	class TestMain;
#endif

class GameSceneEventCB : public ISceneEventCB
{
protected:
#ifdef ENABLE_UNIT_TEST
	MySharedPtr<TestMain> mTestMain;
#endif

public:
    // 场景加载完成处理事件
	virtual void onLevelLoaded() override;
 
protected:
	void runTest();
	void init();
};