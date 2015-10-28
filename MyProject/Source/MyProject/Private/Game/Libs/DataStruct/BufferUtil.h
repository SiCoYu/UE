#ifndef __BUFFERUTIL_H
#define __BUFFERUTIL_H

class BufferUtil
{
public:
	/**
	 *@brief 交换缓冲区中的内容，dest 和 source 开始处的 count 个自己交换，自己保证不越界
	 */
	static void* memSwap(void* dest, void* source, size_t count);
};

#endif		// __BUFFERUTIL_H