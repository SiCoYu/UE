#pragma once

#include "Http.h"
#include "Containers/UnrealString.h"	// FString

/**
 * @brief https://wiki.unrealengine.com/UE4%E4%B8%8EWEB%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%BA%A4%E4%BA%92(json)
 */
class HttpWeb
{
public:
	HttpWeb();

public:
	FString buildJson();
	void sendJson(FString JsonStr);
	void download(FString path);
	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};