#pragma once

#include <string>
#include "Engine/StreamableManager.h"	 // FStreamableManager

/**
 * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
 ue中的异步加载分为两种模式，具体源码在 AsyncLoading.cpp 中
 主线程分帧加载。
 多线程加载。
 可以通过接口判断当前的异步模式是那种模式。
 const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
 */

class FMyStreamableManager
{
public:
	FStreamableManager mStreamableManager;

	FMyStreamableManager();
	~FMyStreamableManager();

	void init();
	void dispose();

	//UObject* GetStreamed(std::string const& path);

	UObject* SynchronousLoad(std::string& path);

	template< typename T >
	T* SynchronousLoadType(std::string& path);

	void RequestAsyncLoad(const std::string& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority = FStreamableManager::DefaultAsyncLoadPriority);

	void RequestAsyncLoad(const FStringAssetReference& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority = FStreamableManager::DefaultAsyncLoadPriority);
};

#include "MyStreamableManager.inl"