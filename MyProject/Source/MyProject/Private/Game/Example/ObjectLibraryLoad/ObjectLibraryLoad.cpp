#include "MyProject.h"
#include "ObjectLibraryLoad.h"

UObjectLibraryLoad::UObjectLibraryLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void UObjectLibraryLoad::LoadAssetDataFromPath(Class* BaseClass, bool bFullyLoad)
{
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(BaseClass, false, GIsEditor);
		ObjectLibrary->AddToRoot();
	}

	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/PathWithAllObjectsOfSameType");
	if (bFullyLoad)
	{
		ObjectLibrary->LoadAssetsFromAssetData();
	}
}

void UObjectLibraryLoad::GetAssetDataFromPath()
{
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData& AssetData = AssetDatas[i];

		const FString* FoundTypeNameString = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UAssetObject, TypeName));

		if (FoundTypeNameString && FoundTypeNameString->Contains(TEXT("FooType")))
		{
			return AssetData;
		}
	}
}