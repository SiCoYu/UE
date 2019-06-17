#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 帧间隔
 */
class FrameInterval
{
protected:
	int mInterval;   // 帧间隔
    int mTotalFrame;      // 总共帧
    int mCurFrame;	    // 当前帧

public:
	FrameInterval();

	void setInterval(int value);
	void setTotalFrame(int value);
	void setCurFrame(int value);
	bool canExec(int delta);
};

MY_END_NAMESPACE