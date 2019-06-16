#pragma once

#include "Containers/UnrealString.h"	// FString
#include "GenericPlatform/GenericPlatformFile.h"	// FDirectoryVisitor
#include "MyFileDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MyDirectoryVisitor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
{
public:
	MyDirectoryVisitor(MyTraverseDirectoryDelegate fileVisitDelegate, MyTraverseDirectoryDelegate directoryVisitDelegate);
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;

private:
	MyTraverseDirectoryDelegate mFileVisitDelegate;
	MyTraverseDirectoryDelegate mDirectoryVisitDelegate;
};

MY_END_NAMESPACE