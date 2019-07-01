#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class SoundPlayState
{
	eSS_None,           // 默认状态
	eSS_Play,           // 播放状态
	eSS_Stop,           // 暂停状态
	eSS_Pause,          // 停止状态
};

MY_END_NAMESPACE