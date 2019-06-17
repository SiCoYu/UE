#include "MyProject.h"
#include "UtilStr.h"
#include "Symbolic.h"
#include <cctype>		// tolower
#include <algorithm>	// transform

MY_BEGIN_NAMESPACE(MyNS)

std::string UtilStr::msDefaultStr = "";
std::string UtilStr::msFormatVar0 = "{0}";
std::string UtilStr::msFormatVar1 = "{1}";
std::string UtilStr::msFormatVar2 = "{2}";
std::string UtilStr::msFormatVar3 = "{3}";
std::string UtilStr::msFormatVar4 = "{4}";
std::string UtilStr::msFormatVar5 = "{5}";
std::string UtilStr::msFormatVar6 = "{6}";
std::string UtilStr::msFormatVar7 = "{7}";
std::string UtilStr::msFormatVar8 = "{8}";
std::string UtilStr::msFormatVar9 = "{9}";

//std::string UtilStr::Format(const char * format, ...)
//{
//	return "";
//}

std::string UtilStr::Format(
	std::string formatStr,
	std::string& var0,
	std::string& var1,
	std::string& var2,
	std::string& var3,
	std::string& var4,
	std::string& var5,
	std::string& var6,
	std::string& var7,
	std::string& var8,
	std::string& var9
)
{
	std::string ret = UtilStr::msDefaultStr;
	std::string::size_type pos(0);

	if (!UtilStr::IsNullOrEmpty(formatStr))
	{
		if (!UtilStr::IsNullOrEmpty(var0))
		{
			if ((pos = formatStr.find(UtilStr::msFormatVar0, pos)) != std::string::npos)
			{
				formatStr = formatStr.replace(pos, UtilStr::msFormatVar0.length(), var0);
			}
		}
	}

	return ret;
}

bool UtilStr::IsNullOrEmpty(std::string& value)
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

FName UtilStr::ConvStdStr2FName(std::string& stdStr)
{
	FName ConvertedFString = FName(stdStr.c_str());
	return ConvertedFString;
}

FName UtilStr::ConvFString2FName(FString& fStr)
{
	FName ConvertedFString = FName(*fStr);
	return ConvertedFString;
}

FString UtilStr::ConvStdStr2FString(std::string& stdStr)
{
	FString fStr(stdStr.c_str());
	return fStr;
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
	//return FTextFormat::FromString(fStr).GetSourceText();
	return FText::FromString(fStr);
}

const FString UtilStr::ConvFText2FString(FText& fText)
{
	//return FTextFormat(fText).GetSourceString();
	return fText.ToString();
}

FText UtilStr::ConvChar2FText(const char* pchar)
{
	return FText::FromString(pchar);
}

const TCHAR* UtilStr::convFStr2TCHAR(FString& fStr)
{
	return *fStr;
}

const TCHAR* UtilStr::convStdStr2TCHAR(std::string& stdStr)
{
	const TCHAR* retChar = nullptr;
	retChar = ANSI_TO_TCHAR(stdStr.c_str());
	return retChar;
}

FName UtilStr::ConvFText2FName(FText& fText)
{
	FName ret = FName(*(fText.ToString()));
	return ret;
}

FText UtilStr::ConvFName2FText(FName& fName)
{
	FText ret = FText::FromName(fName);
	return ret;
}

FText UtilStr::ConvStdStr2FText(std::string& stdStr)
{
	FString fStr(stdStr.c_str());
	return FText::FromString(fStr);
}

std::string& UtilStr::replaceAll(std::string& srcStr, const  std::string& old_value, const std::string& new_value)
{
	while (true)
	{
		std::string::size_type pos(0);

		if ((pos = srcStr.find(old_value)) != std::string::npos)
		{
			srcStr.replace(pos, old_value.length(), new_value);
		}
		else 
		{
			break;
		}
	}

	return srcStr;
}

std::string& UtilStr::replaceAllDistinct(std::string& srcStr, const  std::string& old_value, const std::string& new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
	{
		if ((pos = srcStr.find(old_value, pos)) != std::string::npos)
		{
			srcStr.replace(pos, old_value.length(), new_value);
		}
		else 
		{ 
			break; 
		}
	}

	return srcStr;
}

void UtilStr::split(std::string& srcStr, std::string& delim, std::vector< std::string >* ret)
{
	size_t last = 0;
	size_t index = srcStr.find_first_of(delim, last);

	while (index != std::string::npos)
	{
		ret->push_back(srcStr.substr(last, index - last));
		last = index + 1;
		index = srcStr.find_first_of(delim, last);
	}

	if (index - last>0)
	{
		ret->push_back(srcStr.substr(last, index - last));
	}
}

void UtilStr::removeLastCR(std::string& srcStr)
{
	if (!UtilStr::IsNullOrEmpty(srcStr))
	{
		if (srcStr[srcStr.length() - 1] == Symbolic::CR)
		{
			srcStr = srcStr.substr(0, srcStr.length() - 1);
		}
	}
}

void UtilStr::toLower(std::string& srcStr)
{
	transform(srcStr.begin(), srcStr.end(), srcStr.begin(), ::tolower);
}

void UtilStr::toUpper(std::string& srcStr)
{
	transform(srcStr.begin(), srcStr.end(), srcStr.begin(), ::toupper);
}

MY_END_NAMESPACE