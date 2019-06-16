#include "MyProject.h"
#include "MyDirectoryVisitor.h"

MY_BEGIN_NAMESPACE(MyNS)

MyDirectoryVisitor::MyDirectoryVisitor(MyTraverseDirectoryDelegate fileVisitDelegate, MyTraverseDirectoryDelegate directoryVisitDelegate)
{
	this->mFileVisitDelegate = fileVisitDelegate;
	this->mDirectoryVisitDelegate = directoryVisitDelegate;
}

bool MyDirectoryVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	if (bIsDirectory)
	{
		return this->mDirectoryVisitDelegate.call(FilenameOrDirectory, FString(), FString());
	}
	else
	{
		return this->mFileVisitDelegate.call(FilenameOrDirectory, FString(), FString());
	}
}

MY_END_NAMESPACE