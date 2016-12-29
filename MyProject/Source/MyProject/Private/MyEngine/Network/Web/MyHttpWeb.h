#pragma once

#include "MyProject.h"
#include "Http.h"
#include "MyHttpWeb.generated.h"

/**
 * @brief https://wiki.unrealengine.com/UE4%E4%B8%8EWEB%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%BA%A4%E4%BA%92(json)
 */
UCLASS(config = Game)
class UMyHttpWeb : public UObject
{
	GENERATED_BODY()

public:
	UMyHttpWeb(const FObjectInitializer& ObjectInitializer);
	FString buildJson();
	void sendJson(FString JsonStr);
	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};