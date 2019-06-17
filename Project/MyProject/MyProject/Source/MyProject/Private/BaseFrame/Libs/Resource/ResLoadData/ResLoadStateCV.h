#ifndef __ResLoadStateCV_H
#define __ResLoadStateCV_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class ResLoadStateCV
{
	eNotLoad,       // 没有加载
	eLoading,       // 正在加载
	eLoaded,        // 加载成功
	eFailed,         // 加载失败

	// 实例化状态
	eNotIns,        // 没有实例化
	eInsing,        // 正在实例化
	eInsSuccess,        // 实例化完成
	eInsFailed,     // 实例化失败
};

MY_END_NAMESPACE

#endif