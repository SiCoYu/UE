#pragma once

#include "Containers/UnrealString.h"	// FString
#include "GenericPlatform/GenericPlatformFile.h"	// FDirectoryVisitor
#include "MyFileDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MyDirectoryVisitorHandle
{
public:
	MyDirectoryVisitorHandle(TArray<FString>& outArray);

	bool OnVisitFileHandle(FString absoluteSourcePath, FString absoluteDestPath, FString fileName);
	bool OnVisitDirectoryHandle(FString absoluteSourcePath, FString absoluteDestPath, FString fileName);

private:
	TArray<FString>& mFileArray;
};

MY_END_NAMESPACE