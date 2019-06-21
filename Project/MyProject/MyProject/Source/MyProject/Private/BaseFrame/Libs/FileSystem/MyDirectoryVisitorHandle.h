#pragma once

#include "Containers/UnrealString.h"	// FString
#include "GenericPlatform/GenericPlatformFile.h"	// FDirectoryVisitor
#include "MyFileDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MyDirectoryVisitorHandle
{
public:
	MyDirectoryVisitorHandle(TArray<FString>& outFileArrayRef, TArray<FString>& outDirectoryArrayRef);
	MyDirectoryVisitorHandle(TArray<FString>* outFileArrayPtr, TArray<FString>* outDirectoryArrayPtr);

	bool OnVisitFileHandleRef(FString absoluteSourcePath, FString absoluteDestPath, FString fileName);
	bool OnVisitDirectoryHandleRef(FString absoluteSourcePath, FString absoluteDestPath, FString fileName);

	bool OnVisitFileHandlePtr(FString absoluteSourcePath, FString absoluteDestPath, FString fileName);
	bool OnVisitDirectoryHandlePtr(FString absoluteSourcePath, FString absoluteDestPath, FString fileName);

private:
	TArray<FString>& mFileArrayRef;
	TArray<FString>& mDirectoryArrayRef;

	TArray<FString>* mFileArrayPtr;
	TArray<FString>* mDirectoryArrayPtr;
};

MY_END_NAMESPACE