#ifndef __UtilStr_H
#define __UtilStr_H

#include "CString.h"
#include "UnrealString.h"	// FString
#include "NameTypes.h"		// FName
#include "Internationalization/Text.h"	// FText
#include <string>
#include <vector>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilStr
{
public:
	static std::string msDefaultStr;
	static std::string msFormatVar0;
	static std::string msFormatVar1;
	static std::string msFormatVar2;
	static std::string msFormatVar3;
	static std::string msFormatVar4;
	static std::string msFormatVar5;
	static std::string msFormatVar6;
	static std::string msFormatVar7;
	static std::string msFormatVar8;
	static std::string msFormatVar9;

public:
	//static std::string Format(const char * format, ...);
	static std::string Format(
		std::string formatStr, 
		std::string& var0 = UtilStr::msDefaultStr, 
		std::string& var1 = UtilStr::msDefaultStr,
		std::string& var2 = UtilStr::msDefaultStr,
		std::string& var3 = UtilStr::msDefaultStr,
		std::string& var4 = UtilStr::msDefaultStr,
		std::string& var5 = UtilStr::msDefaultStr,
		std::string& var6 = UtilStr::msDefaultStr,
		std::string& var7 = UtilStr::msDefaultStr,
		std::string& var8 = UtilStr::msDefaultStr,
		std::string& var9 = UtilStr::msDefaultStr
	);
	static bool IsNullOrEmpty(std::string& value);

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
	static FName ConvStdStr2FName(std::string& stdStr);
	static FName ConvFString2FName(FString& fStr);
	static FString ConvStdStr2FString(std::string& stdStr);
	static std::string ConvFString2StdStr(FString& fStr);
	static int32 ConvFString2Int(FString& fStr);
	static float ConvFString2Float(FString& fStr);
	static FString ConvInt2FString(int32& iValue);
	static FString ConvFloat2FString(float& fValue);
	static FText ConvFString2FText(FString& fStr);
	static const FString ConvFText2FString(FText& fText);
	static FText ConvChar2FText(const char* pchar);

	static const TCHAR* convFStr2TCHAR(FString& fStr);
	static const TCHAR* convStdStr2TCHAR(std::string& stdStr);
	static FName ConvFText2FName(FText& fText);
	static FText ConvFName2FText(FName& fName);
	static FText ConvStdStr2FText(std::string& stdStr);

	static std::string& replaceAll(std::string& srcStr, const  std::string& old_value, const std::string& new_value);
	static std::string& replaceAllDistinct(std::string& srcStr, const  std::string& old_value, const std::string& new_value);

	//注意：当字符串为空时，也会返回一个空字符串  
	static void split(std::string& srcStr, std::string& delim, std::vector< std::string >* ret);
	static void removeLastCR(std::string& srcStr);
	static void toLower(std::string& srcStr);
	static void toUpper(std::string& srcStr);

	static inline int lastIndexOf(std::string& srcStr, std::string& delim);
	static inline int length(std::string& srcStr);
};

MY_END_NAMESPACE

#endif