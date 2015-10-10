#ifndef __BufferCV_H
#define __BufferCV_H

namespace BufferCV
{
	//enum BufferCV
	enum
	{
		INIT_ELEM_CAPACITY = 32,              // 默认分配 32 元素
		INIT_CAPACITY = 1 * 1024,             // 默认分配 1 K
		MAX_CAPACITY = 8 * 1024 * 1024,		// 最大允许分配 8 M
	};
}

#endif