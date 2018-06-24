#pragma once

#include "ISceneInputNotify.h"
#include "TypeDef.h"
#include "PlatformDefine.h"

// error C4099: 'FKey': type name first seen using 'struct' now seen using 'class'
// class FKey;
struct FKey;

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class GameSceneInputNotify : public ISceneInputNotify
{
public:
	GameSceneInputNotify();

	void init();
	void dispose();

	void onKeyDown(uint eventId, IDispatchObject* dispObj);
	void onKeyUp(uint eventId, IDispatchObject* dispObj);
	void onMouseDown();
	void onMouseUp();
};

MY_END_NAMESPACE