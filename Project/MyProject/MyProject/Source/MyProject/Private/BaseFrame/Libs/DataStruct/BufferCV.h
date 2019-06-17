#ifndef __BufferCV_H
#define __BufferCV_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class BufferCV
{
	eINIT_ELEM_CAPACITY = 32,              // 默认分配 32 元素
	eINIT_CAPACITY = 1 * 1024,             // 默认分配 1 K
	eMAX_CAPACITY = 8 * 1024 * 1024,		// 最大允许分配 8 M
};

MY_END_NAMESPACE

#endif