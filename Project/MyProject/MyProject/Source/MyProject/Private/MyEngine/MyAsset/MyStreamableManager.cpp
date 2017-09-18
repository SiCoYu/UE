#include "MyProject.h"
#include "Misc/StringAssetReference.h"	// FStringAssetReference
#include "UtilStr.h"
#include <string>
#include "EngineApi.h"	// isMultithreaded
#include "MyStreamableManager.h"
//#include "Serialization/AsyncLoadingThread.h"		// FAsyncLoadingThread ,这个目录是错误的，需要如下目录
// UE4 4.17 这个会导致链接错误
// error LNK2001: unresolved external symbol "private: static bool FAsyncLoadingThread::bThreadStarted" (?bThreadStarted@FAsyncLoadingThread@@0_NA)
// #include "Private/Serialization/AsyncLoadingThread.h"		// FAsyncLoadingThread

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
//  StreamableManager::GetStreamed 私有函数，不能调用
//	return mStreamableManager.GetStreamed(assetRef);
//}

UObject* FMyStreamableManager::SynchronousLoad(std::string& path)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(path));
	// UE4 4.17 : warning C4996: 'FStreamableManager::SynchronousLoad': Call LoadSynchronous with bManageActiveHandle=true instead if you want the manager to keep the handle alive Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//return mStreamableManager.SynchronousLoad(assetRef);
	return mStreamableManager.LoadSynchronous(assetRef, true);
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
	// UE4 4.17 这个会导致链接错误
	// error LNK2001: unresolved external symbol "private: static bool FAsyncLoadingThread::bThreadStarted" (?bThreadStarted@FAsyncLoadingThread@@0_NA)
	//const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
	//return bIsMultithreaded;
	
	return EngineApi::isMultithreaded();
}