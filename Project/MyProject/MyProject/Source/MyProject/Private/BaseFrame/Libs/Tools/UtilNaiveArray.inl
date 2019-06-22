#ifndef __UtilNaiveArray_H
#error "UtilNaiveArray.inl file can only include in UtilNaiveArray.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

template<typename InElementType>
int32 UtilNaiveArray::Num(const TArray<InElementType>& array)
{
	return array.Num();
}

MY_END_NAMESPACE