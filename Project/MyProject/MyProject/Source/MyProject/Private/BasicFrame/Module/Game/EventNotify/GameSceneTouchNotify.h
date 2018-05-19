#pragma once

#include "ISceneTouchNotify.h"

// error C4099: 'FKey': type name first seen using 'struct' now seen using 'class'
// class FKey;
struct FKey;

class GameSceneLogicNotify : public ISceneTouchNotify
{
public:
	GameSceneLogicNotify();
	void onKeyDown(FKey keyCode);
	void onKeyUp(FKey keyCode);
	void onMouseDown();
	void onMouseUp();
};