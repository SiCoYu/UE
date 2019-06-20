#include "MyProject.h"
#include "MyObjectLibrary.h"
#include "Engine/ObjectLibrary.h"	// ObjectLibrary
#include "UObject/UObjectGlobals.h"	  // Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectGlobals.h    ConstructObject

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
	this->mObjectLibrary = ConstructObject<UObjectLibrary>(UObjectLibrary::StaticClass());
}

void MyObjectLibrary::dispose()
{

}

int32 MyObjectLibrary::LoadAssetDataFromPath(const FString& Path)
{
	mObjectLibrary->LoadAssetDataFromPath(Path);
}

MY_END_NAMESPACE