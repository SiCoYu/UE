#ifndef __UtilStr_H_
#define __UtilStr_H_

#include <string>

class UtilStr
{
public:
	static std::string m_sDefaultStr;

public:
	static std::string Format(const char * format, ...);
	static bool IsNullOrEmpty(std::string value);
};

#endif