#pragma once

#include "HAL/Platform.h"		// int32
#include "Containers/UnrealString.h"	// FString
//#include "Engine/ObjectLibrary.h"		// UObjectLibrary
#include "PlatformDefine.h"

class UObjectLibrary;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @ref http://www.manew.com/thread-110292-1-1.html
 */
//UCLASS()
//class UMyObjectLibrary : public 

class MyObjectLibrary
{
	//GENERATED_BODY()

public:
	UObjectLibrary* mObjectLibrary;

public:
	//UMyObjectLibrary();
	//~UMyObjectLibrary();
	MyObjectLibrary();

	void init();
	void dispose();

	int32 LoadAssetDataFromPath(const FString& Path);
};

MY_END_NAMESPACE