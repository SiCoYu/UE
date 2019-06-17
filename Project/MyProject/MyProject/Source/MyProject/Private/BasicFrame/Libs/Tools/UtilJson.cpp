#include "MyProject.h"
#include "UtilJson.h"
#include "UtilFileIO.h"

MY_BEGIN_NAMESPACE(MyNS)

bool UtilJson::loadJsonFromFile(FString& absolutePath, TSharedPtr<FJsonObject>& outRoot)
{
	bool ret = false;
	FString strContent;
	if (UtilFileIO::LoadFileToString(absolutePath, strContent))
	{
		ret = UtilJson::loadJsonFromStr(strContent, outRoot);
	}
	return ret;
}

bool UtilJson::loadJsonFromStr(FString& strContent, TSharedPtr<FJsonObject>& outRoot)
{
	bool ret = false;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(strContent);
	ret = FJsonSerializer::Deserialize(Reader, outRoot);
	return ret;
}

bool UtilJson::getJsonAttrStr(TSharedPtr<FJsonObject>& jsonObject, FString& inKey, FString& outValue)
{
	bool ret = false;

	if (jsonObject->HasField(inKey))
	{
		ret = true;
		outValue = jsonObject->GetStringField(inKey);
	}

	return ret;
}

bool UtilJson::getJsonAttrArray(TSharedPtr<FJsonObject>& jsonObject, FString& inKey, const TArray< TSharedPtr<FJsonValue> >*& outValue)
{
	bool ret = false;

	if (jsonObject->TryGetArrayField(inKey, outValue))
	{
		ret = true;
	}

	return ret;
}

bool UtilJson::convertJsonValueAsString(TSharedPtr<FJsonValue>& jsonValue, FString& outValue)
{
	bool ret = false;
	outValue = jsonValue->AsString();
	return ret;
}

MY_END_NAMESPACE