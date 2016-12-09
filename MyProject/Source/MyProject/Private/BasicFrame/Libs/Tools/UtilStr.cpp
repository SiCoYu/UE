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

FName UtilStr::ConvFString2FName(FString& fStr)
{
	FName ConvertedFString = FName(*fStr);
	return ConvertedFString;
}

FString UtilStr::ConvStdStr2FString(std::string& stdStr)
{
	FString HappyString(stdStr.c_str());
	return HappyString;
}

std::string UtilStr::ConvFString2StdStr(FString& fStr)
{
	std::string MyStdString(TCHAR_TO_UTF8(*fStr));
	return MyStdString;
}

int32 UtilStr::ConvFString2Int(FString& fStr)
{
	int32 MyShinyNewInt = FCString::Atoi(*fStr);
	return MyShinyNewInt;
}

float UtilStr::ConvFString2Float(FString& fStr)
{
	float MyShinyNewFloat = FCString::Atof(*fStr);
	return MyShinyNewFloat;
}

FString UtilStr::ConvInt2FString(int32& iValue)
{
	FString NewString = FString::FromInt(iValue);
	return MyShinyNewFloat;
}

FString UtilStr::ConvFloat2FString(float& fValue)
{
	FString VeryCleanString = FString::SanitizeFloat(fValue);
	return MyShinyNewFloat;
}