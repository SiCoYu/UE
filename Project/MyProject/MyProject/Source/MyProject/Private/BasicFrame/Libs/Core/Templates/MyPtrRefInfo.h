#pragma once

#include "MThreadSafeCounter.h"
#include "GObject.h"

MY_BEGIN_NAMESPACE(MyNS)

class PtrRefInfo : public GObject
{
public:
	inline PtrRefInfo()
		: mRefCount(1)
	{
			
	}

	virtual ~PtrRefInfo()
	{
			
	}

	MThreadSafeCounter mRefCount;
	MThreadSafeCounter mWeakRefCount;
};

MY_END_NAMESPACE