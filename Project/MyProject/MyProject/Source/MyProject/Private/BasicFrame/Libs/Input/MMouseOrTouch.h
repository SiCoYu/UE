#pragma once

#include "GObject.h"
#include "IDispatchObject.h"
#include "InputCoreTypes.h"		// FKey \ EKeys
#include "Math/Vector.h"		// FVector
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MMouseOrTouch : public GObject, public IDispatchObject
{
public:
	FKey mKey;
	FVector mPos;             // Current position of the mouse or touch event
    FVector mLastPos;         // Previous position of the mouse or touch event
    FVector mDelta;           // Delta since last update
    FVector mTotalDelta;      // Delta since the event started being tracked

    float mSensitivity;   // 灵敏度
    int mTouchIndex;  // 触碰索引或者鼠标 // 0 左键 1 右键 2 中键 

public:
	MMouseOrTouch();

	int getTouchIndex();

    // 获取 X 方向移动的距离
	float getXOffset();
    // 获取 X 方向移动的距离
	float getYOffset();
	bool isPosChanged();
};

MY_END_NAMESPACE