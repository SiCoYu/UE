#include "MyProject.h"
#include "UtilStr.h"

std::string UtilStr::msDefaultStr = "";

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

std::string& UtilStr::replaceAll(std::string& str, const  std::string& old_value, const std::string& new_value)
{
	while (true)
	{
		std::string::size_type pos(0);
		if ((pos = str.find(old_value)) != std::string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else 
		{
			break;
		}
	}

	return str;
}

std::string& UtilStr::replaceAllDistinct(std::string& str, const  std::string& old_value, const std::string& new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != std::string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else 
		{ 
			break; 
		}
	}

	return str;
}