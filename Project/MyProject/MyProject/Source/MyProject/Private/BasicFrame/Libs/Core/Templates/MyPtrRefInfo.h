#pragma once

#include "MThreadSafeCounter.h"

namespace MyNS
{
	struct PtrRefInfo
	{
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
}