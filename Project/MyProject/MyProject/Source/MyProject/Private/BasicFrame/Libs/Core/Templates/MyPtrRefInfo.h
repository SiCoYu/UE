#pragma once

#include "MThreadSafeCounter.h"
#include "GObject.h"

namespace MyNS
{
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
}