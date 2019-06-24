#include "MyProject.h"
#include "MyDirectoryVisitorHandle.h"

MY_BEGIN_NAMESPACE(MyNS)

// error C2059: syntax error: 'this'
// error C2530: 'MyNS::MyDirectoryVisitorHandle::mFileArray': references must be initialized
MyDirectoryVisitorHandle::MyDirectoryVisitorHandle(TArray<FString>& outFileArrayRef, TArray<FString>& outDirectoryArrayRef)
//	: this->mFileArray(outArray)
	: mFileArrayRef(outFileArrayRef)
	, mDirectoryArrayRef(outDirectoryArrayRef)
{

}

MyDirectoryVisitorHandle::MyDirectoryVisitorHandle(TArray<FString>* outFileArrayPtr, TArray<FString>* outDirectoryArrayPtr)
	: mFileArrayRef(*outFileArrayPtr)
	, mDirectoryArrayRef(*outDirectoryArrayPtr)
	, mFileArrayPtr(outFileArrayPtr)
	, mDirectoryArrayPtr(outDirectoryArrayPtr)
{

}

bool MyDirectoryVisitorHandle::OnVisitFileHandleRef(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	this->mFileArrayRef.Push(absoluteSourcePath);
	return true;
}

bool MyDirectoryVisitorHandle::OnVisitDirectoryHandleRef(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	this->mDirectoryArrayRef.Push(absoluteSourcePath);
	return true;
}

bool MyDirectoryVisitorHandle::OnVisitFileHandlePtr(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	if (nullptr != this->mFileArrayPtr)
	{
		this->mFileArrayPtr->Push(absoluteSourcePath);
	}
	return true;
}

bool MyDirectoryVisitorHandle::OnVisitDirectoryHandlePtr(FString absoluteSourcePath, FString absoluteDestPath, FString fileName)
{
	if (nullptr != this->mDirectoryArrayPtr)
	{
		this->mDirectoryArrayPtr->Push(absoluteSourcePath);
	}
	return true;
}

MY_END_NAMESPACE