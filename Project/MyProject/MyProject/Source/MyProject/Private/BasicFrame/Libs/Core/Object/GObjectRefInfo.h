#pragma once

#include "MThreadSafeCounter.h"

namespace MyNS
{
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
}