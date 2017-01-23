#pragma once

#include <string>
#include "Engine/StreamableManager.h"	 // FStreamableManager

/**
 * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
 ue�е��첽���ط�Ϊ����ģʽ������Դ���� AsyncLoading.cpp ��
 ���̷߳�֡���ء�
 ���̼߳��ء�
 ����ͨ���ӿ��жϵ�ǰ���첽ģʽ������ģʽ��
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