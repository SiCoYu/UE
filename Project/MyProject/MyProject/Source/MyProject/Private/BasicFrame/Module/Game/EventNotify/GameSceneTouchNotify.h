#pragma once

#include "ISceneTouchNotify.h"

class FKey;

class GameSceneLogicNotify : public ISceneTouchNotify
{
public:
	GameSceneLogicNotify();
	void onKeyDown(FKey keyCode);
	void onKeyUp(FKey keyCode);
	void onMouseDown();
	void onMouseUp();
};