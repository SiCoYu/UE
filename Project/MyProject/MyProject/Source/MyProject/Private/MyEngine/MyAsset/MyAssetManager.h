#pragma once

#include "Engine/AssetManager.h"	 // UAssetManager
#include "MyAssetManager.generated.h"

/**
 * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
 ue�е��첽���ط�Ϊ����ģʽ������Դ���� AsyncLoading.cpp ��
 ���̷߳�֡���ء�
 ���̼߳��ء�
 ����ͨ���ӿ��жϵ�ǰ���첽ģʽ������ģʽ��
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