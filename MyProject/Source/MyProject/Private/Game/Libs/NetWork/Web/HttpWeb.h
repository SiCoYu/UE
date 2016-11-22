#pragma once

#include "MyProject.h"
#include "Http.h"
#include "HttpWeb.generated.h"

UCLASS(config = Game)
class UHttpWeb : public UObject
{
	GENERATED_BODY()

public:
	UHttpWeb(const FObjectInitializer& ObjectInitializer);
	FString buildJson();
	void sendJson();
	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};