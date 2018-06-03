#pragma once

#include "NumIntervalMode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 数字间隔
 */
public class NumInterval
{
protected:
	float mTotalValue;
    float mCurValue;

    NumIntervalMode mNumIntervalMode;

public:
	NumInterval();

	void setTotalValue(float value);
	void setCurValue(float value);
	void reset();
	bool canExec(float delta);
};

MY_END_NAMESPACE