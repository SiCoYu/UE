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