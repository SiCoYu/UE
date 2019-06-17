#ifndef __BufferUtil_H
#define __BufferUtil_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class BufferUtil
{
public:
	/**
	 *@brief 交换缓冲区中的内容，dest 和 source 开始处的 count 个自己交换，自己保证不越界
	 */
	static void* memSwap(void* dest, void* source, size_t count);
};

MY_END_NAMESPACE

#endif		// __BufferUtil_H