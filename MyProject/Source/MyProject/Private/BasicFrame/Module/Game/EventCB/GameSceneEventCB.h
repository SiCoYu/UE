#pragma once

#include "ISceneEventCB.h"

class GameSceneEventCB : public ISceneEventCB
{
public:
    // 场景加载完成处理事件
	virtual void onLevelLoaded() override;
 
protected:
	void runTest();
	void init();
};