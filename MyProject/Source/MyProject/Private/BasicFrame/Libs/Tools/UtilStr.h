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

	// 查找自字符串出现的位置
	static int IndexOf(std::string& srcStr, std::string subStr);
	// 查找字符串最后出现的位置
	static int LastIndexOf(std::string& srcStr, std::string subStr);
	static std::string Substring(std::string& srcStr, int startIndex);
	static std::string Substring(std::string& srcStr, int startIndex, int length);
};

#endif