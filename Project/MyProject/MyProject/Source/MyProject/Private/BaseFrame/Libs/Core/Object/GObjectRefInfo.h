#pragma once

#include "MThreadSafeCounter.h"

MY_BEGIN_NAMESPACE(MyNS)

struct GObjectRefInfo
{
	inline GObjectRefInfo()
		: mRefCount(1)
	{
			
	}

	virtual ~GObjectRefInfo()
	{
			
	}

	MThreadSafeCounter mRefCount;
	MThreadSafeCounter mWeakRefCount;
};

MY_END_NAMESPACE