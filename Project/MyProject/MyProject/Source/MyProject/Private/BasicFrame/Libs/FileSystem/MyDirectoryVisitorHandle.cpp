#include "MyProject.h"
#include "MyDirectoryVisitorHandle.h"

MY_BEGIN_NAMESPACE(MyNS)

// error C2059: syntax error: 'this'
// error C2530: 'MyNS::MyDirectoryVisitorHandle::mFileArray': references must be initialized
MyDirectoryVisitorHandle::MyDirectoryVisitorHandle(TArray<FString>& outArray)
//	: this->mFileArray(outArray)
	: mFileArray(outArray)
{

}

bool MyDirectoryVisitorHandle::OnVisitFileHandle(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	this->mFileArray.Push(absoluteSourcePath);
	return true;
}

bool MyDirectoryVisitorHandle::OnVisitDirectoryHandle(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	this->mFileArray.Push(absoluteSourcePath);
	return true;
}

MY_END_NAMESPACE