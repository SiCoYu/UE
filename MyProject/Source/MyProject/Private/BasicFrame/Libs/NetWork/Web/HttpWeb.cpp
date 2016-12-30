#include "MyProject.h"
#include "HttpWeb.h"
#include "UtilStr.h"

HttpWeb::HttpWeb()
{
	
}

FString HttpWeb::buildJson()
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

void HttpWeb::sendJson(FString JsonStr)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetURL(TEXT("http://localhost/mywebpage.php"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(JsonStr);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &HttpWeb::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
}

void HttpWeb::download(std::string path)
{
	FString fStrPath = UtilStr::ConvStdStr2FString(path);
	this->download(fStrPath, true);
}

void HttpWeb::download(FString path, bool)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/octet-stream; charset=utf-8"));
	HttpRequest->SetURL(TEXT("http://127.0.0.1/GameWebServer/a.txt"));
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &HttpWeb::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
}

void HttpWeb::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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