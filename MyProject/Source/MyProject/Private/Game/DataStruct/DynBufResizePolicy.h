#ifndef __DYNBUFRESIZEPOLICY_H
#define __DYNBUFRESIZEPOLICY_H

#define MAXCAPACITY 8 * 1024 * 1024      // ���������� 8 M
#define INITCAPACITY 1 * 1024            // Ĭ�Ϸ��� 1 K

class DynBufResizePolicy
{
public:
	static uint32 getCloseSize(uint32 needSize, uint32 capacity)
};


#endif			// __DYNBUFRESIZEPOLICY_H	