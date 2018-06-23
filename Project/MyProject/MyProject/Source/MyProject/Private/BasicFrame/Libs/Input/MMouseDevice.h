#pragma once

#include "MMouseOrTouch.h"
#include "TickMode.h"
#include "MMouseDeviceType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MMouseDevice : public MMouseOrTouch
{
public:
	static MMouseDevice* MouseLeftButton;
    static MMouseDevice* MouseRightButton;
    static MMouseDevice* MouseMiddleButton;

    MMouseDevice* mMouse[MMouseDeviceType::eMouseTotalButton];

public:
	static MMouseDevice* GetMouse(int button);

public:
	MMouseDevice(int button);

	void onTick(float delta, TickMode tickMode);

	void handleMouseDown();
	void handleMouseUp();
	void handleMousePress();
	void handleMousePressOrMove();
	void handleMousePressMove();
};

MY_END_NAMESPACE