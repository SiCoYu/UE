#ifndef __DynBufResizePolicy_H
#define __DynBufResizePolicy_H


class DynBufResizePolicy
{
public:
	static uint32 getCloseSize(
		uint32 needSize, 
		uint32 capacity, 
		uint32 maxCapacity
	);
};


#endif			// __DynBufResizePolicy_H	