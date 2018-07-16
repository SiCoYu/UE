#ifndef __MyStreamableManager_H
#define __MyStreamableManager_H

#include <string>

#include "Engine/StreamableManager.h"	 // FStreamableManager
#include "UObject/SoftObjectPath.h"	// FStringAssetReference\FSoftObjectPath

#include "GObject.h"
#include "PlatformDefine.h"

/**
  * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
  * ue中的 异步加载分为两种模式，具体源码在 AsyncLoading.cpp 中主线程分帧加载。多线程加载。可以通过接口判断当前的异步模式是那种模式。
  * const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
  */

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 没有打包的时候，就是一个默认包，一个一个资源打包的时候，才会有 FPackage
 */
class MyStreamableManager : public GObject
{
public:
	FStreamableManager mStreamableManager;

	MyStreamableManager();
	~MyStreamableManager();

	void init();
	void dispose();

	//UObject* GetStreamed(std::string const& path);

	UObject* SynchronousLoad(std::string& path);
	UObject* SynchronousLoad(FSoftObjectPath& path);

	template< typename T >
	T* SynchronousLoadType(std::string& path);

	void RequestAsyncLoad(const std::string& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority = FStreamableManager::DefaultAsyncLoadPriority);

	void RequestAsyncLoad(const FStringAssetReference& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority = FStreamableManager::DefaultAsyncLoadPriority);

	bool isAsyncLoadComplete(const FSoftObjectPath& Target) const;
	void unload(const FSoftObjectPath& Target);

protected:
	bool IsMultithreaded();
};

MY_END_NAMESPACE

#include "MyStreamableManager.inl"

#endif