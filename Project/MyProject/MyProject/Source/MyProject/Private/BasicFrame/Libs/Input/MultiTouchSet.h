#pragma once

#include "MList.h"
#include "TickMode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;
class MMouseOrTouch;

/**
 * @brief 触碰集合
 */
class MultiTouchSet : public IDispatchObject
{
protected:
	MList<MMouseOrTouch*> mTouchList;

public:
	MultiTouchSet();

	void init();
	void dispose();
	void reset();

	void addTouch(MMouseOrTouch* touch);
	void onTick(float delta, TickMode tickMode);
};

MY_END_NAMESPACE