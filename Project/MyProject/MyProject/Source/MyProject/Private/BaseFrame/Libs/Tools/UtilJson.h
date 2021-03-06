#ifndef __UtilJson_H
#define __UtilJson_H

#include "CString.h"
#include "UnrealString.h"	// FString
#include "NameTypes.h"		// FName
#include "Internationalization/Text.h"	// FText
#include "Json.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @ref https://blog.csdn.net/qq_31930499/article/details/88366530
 * @ref https://www.cnblogs.com/sevenyuan/p/7116686.html
 * @ref https://blog.csdn.net/qq_35760525/article/details/77531286
 */
class UtilJson
{
public:
	static bool loadJsonFromFile(FString& absolutePath, TSharedPtr<FJsonObject>& rRoot);
	static bool loadJsonFromStr(FString& absolutePath, TSharedPtr<FJsonObject>& rRoot);
	static bool getJsonAttrStr(TSharedPtr<FJsonObject>& jsonObject, FString& inKey, FString& outValue);
	static bool getJsonAttrArray(TSharedPtr<FJsonObject>& jsonObject, FString& inKey, const TArray< TSharedPtr<FJsonValue> >*& outValue);
	static bool convertJsonValueAsString(TSharedPtr<FJsonValue>& jsonValue, FString& outValue);
};

MY_END_NAMESPACE

#endif