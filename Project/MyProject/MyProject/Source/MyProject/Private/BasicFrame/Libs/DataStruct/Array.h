#ifndef __Array_H
#define __Array_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 内存操作
 */
class Array
{
public:
	/**
	*@brief 从 src 的 srcIndex 开始处拷贝数据到 dest 地址的 destIndex 偏移处，总共拷贝 length 字节个数
	*/
	static void Copy(void* src, long srcIndex, void* dest, long destIndex, long length);

	/**
	* @brief 交换缓冲区字节顺序
	*/
	static void Reverse(char* buff, int index, int length);
	/**
	* @brief 清除从 index 开始的，长度是 length 的 buff 指定的缓冲区
	*/
	static void Clear(char* buff, int index, int length);
};

#endif