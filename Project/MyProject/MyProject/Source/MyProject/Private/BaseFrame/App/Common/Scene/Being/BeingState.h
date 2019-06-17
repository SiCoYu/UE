#pragma once

#include <string>
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 动画事件名字
*/
class AnimaionEventTimeLine
{
public:
	static float onStartAnimEvent;
};

/**
* @brief 动画事件名字
*/
class AnimaionEventName
{
public:
	static std::string onStartAnimEvent;
};

/**
* @brief 动画事件 Id
*/
enum class AnimaionEventId
{
	eStartAnimEvent = 0,
};

/**
 * @brief 动画名字
 */
class AnimaionName
{
public:
	static std::string eBSIdle;
};

/**
 * @brief Being 状态，状态之间不共存，必然要有一个状态
 */
enum class BeingState
{
	eBSIdle,         // 空闲状态
	eBSWalk,         // 走状态
	eBSRun,          // 跑状态(目前不用这个)
	eBSAttack,       // 攻击(吞食)
	eBSSeparation,   // 分离状态，出生后，不要都聚集在一起，停止的时候也不要都聚集在一起
	eBSBirth,        // 出生状态
	eBSIOControlWalk,// 控制走状态
	eBSSplit,        // 分裂状态
	eBSMoveCenter,   // 向中心移动
};

/**
 * @brief Being 子状态，状态之间不共存，但是可以与 BeingState 功能，状态可以没有
 */
enum class BeingSubState
{
	eBSSNone,         // 空状态
	eBSSContactMerge, // 触碰合并，这个时候还没有真正的合并，需要等到触碰一段时间后，才能合并
	eBSSReqServerMerge, // 请求服务器合并
	eBSSMerge,          // 真正的融合
};

/**
 * @brief 各种动作状态 Id ，通常一个状态可能对应多个动作。动作编码是这样编码的，三位数，从 100 - 999 ，如果是动作过渡，条件是这样的，就是源动作 Id * 100 + 目的动作 Id ，例如源动作 234 ，目的动作是 678 ，那么最终的转换条件是 234 * 100 + 678 = 234678 ，这个就是转换的条件，凡是单独的三位数，都是从 Default 状态转换到目标状态的，例如一个动作编号是 123 ，那么 123 这个条件就是直接到 123 这个动作的条件
 */
enum class BeingActId
{
	eActIdle,
	eActWalk,
	eActRun
};

/**
 * @brief Being 状态过渡
 */
class BeingStateTransit
{
public:
	BeingActId convState2Act(BeingState state);
};

MY_END_NAMESPACE