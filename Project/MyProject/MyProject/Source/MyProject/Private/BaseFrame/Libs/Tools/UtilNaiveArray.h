#ifndef __UtilNaiveArray_H
#define __UtilNaiveArray_H

#include "HAL/Platform.h"	// int32\FORCEINLINE
#include "Containers/Array.h"	// TArray
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilNaiveArray
{
public:
	template<typename InElementType>
	static FORCEINLINE int32 Num(const TArray<InElementType>& array);
};

MY_END_NAMESPACE

#include "UtilNaiveArray.inl"

#endif