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

	// �������ַ������ֵ�λ��
	static int IndexOf(std::string& srcStr, std::string subStr);
	// �����ַ��������ֵ�λ��
	static int LastIndexOf(std::string& srcStr, std::string subStr);
	static std::string Substring(std::string& srcStr, int startIndex);
	static std::string Substring(std::string& srcStr, int startIndex, int length);
};

#endif