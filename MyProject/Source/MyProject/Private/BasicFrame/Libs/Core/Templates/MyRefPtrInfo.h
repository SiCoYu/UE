#pragma once

#include "MThreadSafeCounter.h"

namespace MyNS
{
	struct RefPtrInfo
	{
		inline RefPtrInfo()
			: mRefCount(1)
		{
			
		}

		virtual ~SharedPtrInfo()
		{
			
		}

		MThreadSafeCounter mRefCount;
		MThreadSafeCounter mWeakRefCount;
	};
}