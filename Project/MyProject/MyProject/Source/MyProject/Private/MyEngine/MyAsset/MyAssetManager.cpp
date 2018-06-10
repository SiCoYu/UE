#include "MyProject.h"
#include "MyAssetManager.h"

MyAssetManager::MyAssetManager()
{
	
}

//UMyAssetManager::~UMyAssetManager()
//{
//	
//}

void MyAssetManager::init()
{
	if (UAssetManager::IsValid())
	{
		UAssetManager& AssetManager = UAssetManager::Get();
		TArray<FPrimaryAssetTypeInfo> TypeInfos;
		AssetManager.GetPrimaryAssetTypeInfoList(TypeInfos);
	}
}

void MyAssetManager::dispose()
{

}