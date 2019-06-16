#include "MyProject.h"
#include "MyDirectoryVisitorHandle.h"

MY_BEGIN_NAMESPACE(MyNS)

MyDirectoryVisitorHandle::MyDirectoryVisitorHandle(TArray<FString>& outArray)
	: this->mFileArray(outArray)
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