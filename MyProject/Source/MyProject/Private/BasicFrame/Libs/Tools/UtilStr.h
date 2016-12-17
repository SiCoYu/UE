#ifndef __UtilStr_H_
#define __UtilStr_H_

#include "CString.h"
#include "UnrealString.h"	// FString
#include "NameTypes.h"
#include "Internationalization/Text.h"	// FText
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

	// https://wiki.unrealengine.com/String_Conversions:_FString_to_FName,_FString_to_Int32,_Float_to_FString
	// See CString.h for more details and other functions like
	// atoi64(string to int64)
	// Atod(string to double precision float)
public:
	static FName ConvFString2FName(FString& fStr);
	static FString ConvStdStr2FString(std::string& stdStr);
	static std::string ConvFString2StdStr(FString& fStr);
	static int32 ConvFString2Int(FString& fStr);
	static float ConvFString2Float(FString& fStr);
	static FString ConvInt2FString(int32& iValue);
	static FString ConvFloat2FString(float& fValue);
	static FText ConvFString2FText(FString& fStr);
	static const FString ConvFText2FString(FText& fText);
};

#endif