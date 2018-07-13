#ifndef __UtilFileIO_H
#error "UtilFileIO.inl file can only include in UtilFileIO.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

template<class T0, class T1>
static std::string UtilFileIO::Combine(T0 param0, T1 param1)
{
	std::stringstream strStream;
	strStream << param0 << "/" << "param1";

	return strStream.str();
}

MY_END_NAMESPACE