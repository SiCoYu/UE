#include "MyProject.h"
#include "MyObjectLibrary.h"

MY_BEGIN_NAMESPACE(MyNS)

MyObjectLibrary::MyObjectLibrary()
{
	
}

//UMyObjectLibrary::~UMyObjectLibrary()
//{
//	
//}

void MyObjectLibrary::init()
{
	mObjectLibrary = ConstructObject<UObjectLibrary>(UObjectLibrary::StaticClass());
}

void MyObjectLibrary::dispose()
{

}

int32 MyObjectLibrary::LoadAssetDataFromPath(const FString& Path)
{
	mObjectLibrary->LoadAssetDataFromPath(Path);
}

MY_END_NAMESPACE