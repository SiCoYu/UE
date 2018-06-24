#ifndef __TickPriority_H
#define __TickPriority_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief Tick 的优先级
 * @brief TP TickPriority 缩写
 */
class TickPriority
{
public:
	static float eTPDelayTaskMgr;       // DelayTaskMgr
	static float eTPInputMgr;			// InputMgr
};

MY_END_NAMESPACE

#endif