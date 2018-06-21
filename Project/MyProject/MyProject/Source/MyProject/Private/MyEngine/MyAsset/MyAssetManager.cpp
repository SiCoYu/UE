#include "MyProject.h"
#include "MyAssetManager.h"

MY_BEGIN_NAMESPACE(MyNS)

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