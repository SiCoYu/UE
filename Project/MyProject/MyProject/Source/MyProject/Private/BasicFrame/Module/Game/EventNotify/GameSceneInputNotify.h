#pragma once

#include "ISceneInputNotify.h"
#include "PlatformDefine.h"

// error C4099: 'FKey': type name first seen using 'struct' now seen using 'class'
// class FKey;
struct FKey;

MY_BEGIN_NAMESPACE(MyNS)

class GameSceneInputNotify : public ISceneInputNotify
{
public:
	GameSceneInputNotify();

	void onKeyDown(FKey keyCode);
	void onKeyUp(FKey keyCode);
	void onMouseDown();
	void onMouseUp();
};

MY_END_NAMESPACE