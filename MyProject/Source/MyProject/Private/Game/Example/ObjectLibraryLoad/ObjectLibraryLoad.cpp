#include "MyProject.h"
#include "ObjectLibraryLoad.h"

UObjectLibraryLoad::UObjectLibraryLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

// UClass ���� Class
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

		// ��һ��ԭ���������ģ����ǲ�֪����ô�޸ģ� UAssetObject ��һ�����ͣ� TypeName �������е�һ������
		//const FString* FoundTypeNameString = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UAssetObject, TypeName));
		// ��̬��Ա���
		const FString* FoundTypeNameString = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UStaticMesh, bAutoComputeLODScreenSize));

		if (FoundTypeNameString && FoundTypeNameString->Contains(TEXT("FooType")))
		{
			return AssetData;
		}
	}

	return FAssetData();
}