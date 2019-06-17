#ifndef __ResLoadPriority_H
#define __ResLoadPriority_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 资源加载优先级
 */
enum class ResLoadPriority
{
	eRLP_Low_1000,          // 普通低
	eRLP_Middle_1000,       // 普通权重
	eRLP_High_1000,         // 普通高
	eRLP_Total,             // 总
};

MY_END_NAMESPACE

#endif