#include "MyProject.h"
#include "MyStreamableManager.h"
#include <string>
// UE 4.19.1  warning : FStringAssetReference has been renamed to FSoftObjectPath, change to #include "UObject/SoftObjectPath.h" and rename references
//#include "Misc/StringAssetReference.h"	// FStringAssetReference
//#include "UObject/SoftObjectPath.h"	// FStringAssetReference
#include "UtilStr.h"
#include "UtilEngineWrap.h"	// isMultithreaded
//#include "Serialization/AsyncLoadingThread.h"		// FAsyncLoadingThread ,这个目录是错误的，需要如下目录
// UE4 4.17 这个会导致链接错误
// error LNK2001: unresolved external symbol "private: static bool FAsyncLoadingThread::bThreadStarted" (?bThreadStarted@FAsyncLoadingThread@@0_NA)
// #include "Private/Serialization/AsyncLoadingThread.h"		// FAsyncLoadingThread

MY_BEGIN_NAMESPACE(MyNS)

MyStreamableManager::MyStreamableManager()
{
	
}

MyStreamableManager::~MyStreamableManager()
{
	
}

void MyStreamableManager::init()
{

}

void MyStreamableManager::dispose()
{

}

//UObject* MyStreamableManager::GetStreamed(std::string const& InTargetName)
//{
//	FStringAssetReference assetRef;
//	assetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(InTargetName)));
//
//	// StreamableManager::GetStreamed 私有函数，不能调用
//	return this->mStreamableManager.GetStreamed(assetRef);
//}

UObject* MyStreamableManager::SynchronousLoad(std::string& path)
{
	// UE 4.19.1  warning : FStringAssetReference has been renamed to FSoftObjectPath, change to #include "UObject/SoftObjectPath.h" and rename references
	//FStringAssetReference assetRef;
	FSoftObjectPath assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(path));

	// UE4 4.17 : warning C4996: 'FStreamableManager::SynchronousLoad': Call LoadSynchronous with bManageActiveHandle=true instead if you want the manager to keep the handle alive Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//return mStreamableManager.SynchronousLoad(assetRef);
	return this->mStreamableManager.LoadSynchronous(assetRef, true);
}

UObject* MyStreamableManager::SynchronousLoad(FSoftObjectPath& path)
{
	UObject* obj = NULL;
	obj = this->mStreamableManager.LoadSynchronous(path, true);
	return obj;
}

void MyStreamableManager::RequestAsyncLoad(const std::string& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(TargetToStream)));

	this->mStreamableManager.RequestAsyncLoad(assetRef, DelegateToCall, Priority);
}

void MyStreamableManager::RequestAsyncLoad(const FStringAssetReference& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	this->mStreamableManager.RequestAsyncLoad(TargetToStream, DelegateToCall, Priority);
}

bool MyStreamableManager::IsMultithreaded()
{
	// UE4 4.17 这个会导致链接错误
	// error LNK2001: unresolved external symbol "private: static bool FAsyncLoadingThread::bThreadStarted" (?bThreadStarted@FAsyncLoadingThread@@0_NA)
	//const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
	//return bIsMultithreaded;
	
	//return UtilEngineWrap::isMultithreaded();
	return UtilEngineWrap::isInAsyncLoadingThread();
}

bool MyStreamableManager::isAsyncLoadComplete(const FSoftObjectPath& Target) const
{
	return this->mStreamableManager.IsAsyncLoadComplete(Target);
}

void MyStreamableManager::unload(const FSoftObjectPath& Target)
{
	this->mStreamableManager.Unload(Target);
}

MY_END_NAMESPACE