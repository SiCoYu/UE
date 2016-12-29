#include "MyProject.h"
#include "MyHttpWeb.h"

UMyHttpWeb::UMyHttpWeb(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

FString UMyHttpWeb::buildJson()
{
	// Create a writer and hold it in this FString
	FString JsonStr;
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("user"), TEXT("StormUnited"));
	JsonWriter->WriteObjectEnd();

	// Close the writer and finalize the output such that JsonStr has what we want
	JsonWriter->Close();

	return JsonStr;
}

void UMyHttpWeb::sendJson(FString JsonStr)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetURL(TEXT("http://localhost/mywebpage.php"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(JsonStr);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UMyHttpWeb::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
}

void UMyHttpWeb::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString MessageBody = "";

	// If HTTP fails client-side, this will still be called but with a NULL shared pointer!
	if (!Response.IsValid())
	{
		MessageBody = "{\"success\":\"Error: Unable to process HTTP Request!\"}";
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		MessageBody = Response->GetContentAsString();
	}
	else
	{
		MessageBody = FString::Printf(TEXT("{\"success\":\"HTTP Error: %d\"}"), Response->GetResponseCode());
	}
}