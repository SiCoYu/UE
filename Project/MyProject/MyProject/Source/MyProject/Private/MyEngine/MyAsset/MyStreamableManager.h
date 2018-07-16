#ifndef __MyStreamableManager_H
#define __MyStreamableManager_H

#include <string>

#include "Engine/StreamableManager.h"	 // FStreamableManager
#include "UObject/SoftObjectPath.h"	// FStringAssetReference\FSoftObjectPath

#include "GObject.h"
#include "PlatformDefine.h"

/**
  * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
  * ue�е� �첽���ط�Ϊ����ģʽ������Դ���� AsyncLoading.cpp �����̷߳�֡���ء����̼߳��ء�����ͨ���ӿ��жϵ�ǰ���첽ģʽ������ģʽ��
  * const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
  */

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief û�д����ʱ�򣬾���һ��Ĭ�ϰ���һ��һ����Դ�����ʱ�򣬲Ż��� FPackage
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