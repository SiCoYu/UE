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
	int32 NewInt = FCString::Atoi(*fStr);
	return NewInt;
}

float UtilStr::ConvFString2Float(FString& fStr)
{
	float NewFloat = FCString::Atof(*fStr);
	return NewFloat;
}

FString UtilStr::ConvInt2FString(int32& iValue)
{
	FString NewString = FString::FromInt(iValue);
	return NewString;
}

FString UtilStr::ConvFloat2FString(float& fValue)
{
	FString NewString = FString::SanitizeFloat(fValue);
	return NewString;
}

FText UtilStr::ConvFString2FText(FString& fStr)
{
	return FTextFormat::FromString(fStr).GetSourceText();
}

const FString UtilStr::ConvFText2FString(FText& fText)
{
	return FTextFormat(fText).GetSourceString();
}