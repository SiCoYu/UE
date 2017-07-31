#include "MyProject.h"
#include "Misc/StringAssetReference.h"	// FStringAssetReference
#include "UtilStr.h"
#include <string>
#include "MyStreamableManager.h"
//#include "Serialization/AsyncLoadingThread.h"		// FAsyncLoadingThread ,���Ŀ¼�Ǵ���ģ���Ҫ����Ŀ¼
#include "Private/Serialization/AsyncLoadingThread.h"		// FAsyncLoadingThread

FMyStreamableManager::FMyStreamableManager()
{
	
}

FMyStreamableManager::~FMyStreamableManager()
{
	
}

void FMyStreamableManager::init()
{

}

void FMyStreamableManager::dispose()
{

}

//UObject* FMyStreamableManager::GetStreamed(std::string const& InTargetName)
//{
//	FStringAssetReference assetRef;
//	assetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(InTargetName)));
//  StreamableManager::GetStreamed ˽�к��������ܵ���
//	return mStreamableManager.GetStreamed(assetRef);
//}

UObject* FMyStreamableManager::SynchronousLoad(std::string& path)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(path));
	return mStreamableManager.SynchronousLoad(assetRef);
}

void FMyStreamableManager::RequestAsyncLoad(const std::string& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(TargetToStream)));
	mStreamableManager.RequestAsyncLoad(assetRef, DelegateToCall, Priority);
}

void FMyStreamableManager::RequestAsyncLoad(const FStringAssetReference& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	mStreamableManager.RequestAsyncLoad(TargetToStream, DelegateToCall, Priority);
}

bool FMyStreamableManager::IsMultithreaded()
{
	const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
	return bIsMultithreaded;
}