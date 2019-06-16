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
}

bool MyDirectoryVisitorHandle::OnVisitDirectoryHandle(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	this->mFileArray.Push(absoluteSourcePath);
}

MY_END_NAMESPACE