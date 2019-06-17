#ifndef __UtilStr_H
#error "UtilStr.inl file can only include in UtilStr.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

int UtilStr::lastIndexOf(std::string& str, std::string& delim)
{
	return str.find_last_of(delim);
}

int UtilStr::length(std::string& str)
{
	return str.length();
}

MY_END_NAMESPACE