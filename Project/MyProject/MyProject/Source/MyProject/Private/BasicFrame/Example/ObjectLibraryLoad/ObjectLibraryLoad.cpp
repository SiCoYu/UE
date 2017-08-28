#include "MyProject.h"
#include "ObjectLibraryLoad.h"

UObjectLibraryLoad::UObjectLibraryLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

// UClass 不是 Class
void UObjectLibraryLoad::LoadAssetDataFromPath(UClass* BaseClass, bool bFullyLoad)
{
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(BaseClass, false, GIsEditor);
		ObjectLibrary->AddToRoot();
	}

	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/PathWithAllObjectsOfSameType"));
	if (bFullyLoad)
	{
		ObjectLibrary->LoadAssetsFromAssetData();
	}
}

FAssetData UObjectLibraryLoad::GetAssetDataFromPath()
{
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData& AssetData = AssetDatas[i];

		// 这一行原来是这样的，但是不知道这么修改， UAssetObject 是一个类型， TypeName 是类型中的一个属性
		//const FString* FoundTypeNameString = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UAssetObject, TypeName));
		// 静态成员检查
		const FString* FoundTypeNameString = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UStaticMesh, bAutoComputeLODScreenSize));

		if (FoundTypeNameString && FoundTypeNameString->Contains(TEXT("FooType")))
		{
			return AssetData;
		}
	}

	return FAssetData();
}