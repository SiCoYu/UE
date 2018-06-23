#pragma once

#include "InputCoreTypes.h"		// FKey \ EKeys
#include "Math/Vector.h"		// FVector

#include "TickMode.h"
#include "MMouseOrTouch.h"
#include "IDispatchObject.h"
#include "MDictionary.h"
#include "MTouchPhase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MTouchDevice;

class MTouchDevice : public MMouseOrTouch
{
public:
    static MDictionary<int, MTouchDevice*> mTouches;

protected:
	/**
	 * @brief UE4 Touch 信息
	 * @code Engine\Source\Runtime\Engine\Private\UserInterface\PlayerInput.cpp
	 * // update touched/untouched flag
	 * // > 0 means that it's currently held down (anything besides an end message is held down)
	 * Touches[Handle].Z = (Type == ETouchType::Ended) ? 0.0f : 1.0f;
	 */
	FVector* mNativeTouchPos;
	/**
	 * @code G:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\InputCore\Private\InputCoreTypes.cpp
	 * static const int32 NUM_TOUCH_KEYS = 11;
	 * static const FKey TouchKeys[NUM_TOUCH_KEYS];
	 * const FKey EKeys::TouchKeys[NUM_TOUCH_KEYS];
	 */
	FKey* mNativeTouch;

	MTouchPhase mTouchPhase;

public:
	static MTouchDevice* GetTouch(int id);

public:
	MTouchDevice(int touchIndex);

	bool _isInBegan();
	bool _isInMoved();
	bool _isInStationary();
	bool _isInEnded();
	bool _isInCanceled();

	void setNativeTouch(FVector* touchPos, FKey* nativeTouch, int touchIndex);
	void onTick(float delta, TickMode tickMode);

	void handleTouchBegan();
	void handleTouchMoved();
	void handleTouchStationary();
	void handleTouchEnded();
	void handleTouchCanceled();
};

MY_END_NAMESPACE