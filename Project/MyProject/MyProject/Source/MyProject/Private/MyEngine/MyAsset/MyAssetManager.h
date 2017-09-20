#pragma once

#include "Engine/AssetManager.h"	 // UAssetManager
#include "MyAssetManager.generated.h"

/**
 * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
 ue中的异步加载分为两种模式，具体源码在 AsyncLoading.cpp 中
 主线程分帧加载。
 多线程加载。
 可以通过接口判断当前的异步模式是那种模式。
 const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
 */

UCLASS()
class UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UMyAssetManager();
	~UMyAssetManager();

	void init();
	void dispose();
};