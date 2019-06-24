#pragma once

#include "Containers/UnrealString.h"	// FString
#include "GenericPlatform/GenericPlatformFile.h"	// FDirectoryVisitor
#include "MyFileDelegate.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

// error C2247: 'MyNS::MyAllocatedObject::operator new' not accessible because 'MyNS::MyDirectoryVisitorHandle' uses 'private' to inherit from 'MyNS::GObject'
//class MyDirectoryVisitorHandle : GObject
class MyDirectoryVisitorHandle : public GObject
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