#pragma once

#include "ISceneEventCB.h"
#include "MySharedPointer.h"
#include "PlatformDefine.h"

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
	GameSceneEventCB();
	virtual ~GameSceneEventCB();

    // 场景加载完成处理事件
	virtual void onLevelLoaded() override;
	virtual void init() override;
	virtual void dispose() override;
 
protected:
	void runTest();
};