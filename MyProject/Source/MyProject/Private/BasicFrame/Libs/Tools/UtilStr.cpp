#include "MyProject.h"
#include "UtilStr.h"

std::string UtilStr::m_sDefaultStr = "";

std::string UtilStr::Format(const char * format, ...)
{
	return "";
}

bool UtilStr::IsNullOrEmpty(std::string value)
{
	if (value == "")
	{
		return true;
	}

	return false;
}

int UtilStr::IndexOf(std::string& srcStr, std::string subStr)
{
	return srcStr.find_first_of(subStr);
}

int UtilStr::LastIndexOf(std::string& srcStr, std::string subStr)
{
	return srcStr.find_last_of(subStr);
}

std::string UtilStr::Substring(std::string& srcStr, int startIndex)
{
	return srcStr.substr(startIndex);
}

std::string UtilStr::Substring(std::string& srcStr, int startIndex, int length)
{
	return srcStr.substr(startIndex, length);
}