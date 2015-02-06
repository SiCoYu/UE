#ifndef __DYNBUFRESIZEPOLICY_H
#define __DYNBUFRESIZEPOLICY_H

#define MAXCAPACITY 8 * 1024 * 1024      // 最大允许分配 8 M
#define INITCAPACITY 1 * 1024            // 默认分配 1 K

class DynBufResizePolicy
{
public:
	static uint32 getCloseSize(uint32 needSize, uint32 capacity)
};


#endif			// __DYNBUFRESIZEPOLICY_H	