#ifndef __DynBufResizePolicy_H
#define __DynBufResizePolicy_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class DynBufResizePolicy
{
public:
	static uint32 getCloseSize(
		uint32 needSize, 
		uint32 capacity, 
		uint32 maxCapacity
	);
};

MY_END_NAMESPACE

#endif			// __DynBufResizePolicy_H	