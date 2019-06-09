#pragma once

#include "GObject.h"
#include "ISceneEventNotify.h"
#include "MySharedPointer.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

#ifdef ENABLE_UNIT_TEST
	class TestMain;
#endif

class GameSceneEventNotify : public GObject/*, public ISceneEventNotify*/
{
protected:
#ifdef ENABLE_UNIT_TEST
	MySharedPtr<TestMain> mTestMain;
#endif

public:
	GameSceneEventNotify();
	virtual ~GameSceneEventNotify();

	virtual void init() override;
	virtual void dispose() override;

	// 场景加载完成处理事件
	virtual void onLevelLoaded() /*override*/;
 
protected:
	void runTest();
};

MY_END_NAMESPACE