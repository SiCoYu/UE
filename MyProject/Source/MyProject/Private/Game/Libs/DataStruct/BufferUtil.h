#ifndef __BUFFERUTIL_H
#define __BUFFERUTIL_H

class BufferUtil
{
public:
	/**
	 *@brief 交换缓冲区中的内容，dest 和 source 开始处的 count 个自己交换，自己保证不越界
	 */
	static void* memSwap(void* dest, void* source, size_t count);
	/**
	 *@brief 从 src 的 srcIndex 开始处拷贝数据到 dest 地址的 destIndex 偏移处，总共拷贝 length 字节个数
	 */
	static void Copy(void* src, long srcIndex, void* dest, long destIndex, long length);

	/**
	 * @brief 交换缓冲区字节顺序
	 */
	static void Reverse(char* buff, int index, int length);

	static void Clear(char* buff, int index, int length);
};

#endif		// __BUFFERUTIL_H