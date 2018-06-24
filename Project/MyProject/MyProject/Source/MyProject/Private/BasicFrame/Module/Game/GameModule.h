#pragma once

#include "GObject.h"
#include "IGameModule.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GameRouteNotify;
class GameNetNotify;
class GameUiEventNotify;
class GameSceneEventNotify;
class GameSceneInputNotify;

class GameModule : public GObject, public IGameModule
{
protected:
	GameRouteNotify* mGameRouteNotify;
	GameNetNotify* mGameNetNotify;
    //GotoScene mGotoScene;
    GameUiEventNotify* mGameUiEventNotify;
	GameSceneEventNotify* mGameSceneEventNotify;
	GameSceneInputNotify* mGameSceneTouchNotify;

public:
	GameModule();

	void init();
	void dispose();

	void initGVar();
	void loadGameScene();
};

MY_END_NAMESPACE