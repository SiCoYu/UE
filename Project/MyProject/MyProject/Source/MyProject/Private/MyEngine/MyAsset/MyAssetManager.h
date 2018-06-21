#pragma once

#include "Engine/AssetManager.h"	 // UAssetManager
//#include "MyAssetManager.generated.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief http://blog.csdn.net/yangxuan0261/article/details/54408683
 * ue�е��첽���ط�Ϊ����ģʽ������Դ���� AsyncLoading.cpp ��. ���̷߳�֡���ء� ���̼߳��ء� ����ͨ���ӿ��жϵ�ǰ���첽ģʽ������ģʽ��
 * const bool bIsMultithreaded = FAsyncLoadingThread::IsMultithreaded();
 * @src Engine\Source\Runtime\Engine\Classes\Engine\AssetManager.h
 * @ref Engine\Plugins\Editor\AssetManagerEditor\Source\AssetManagerEditor\Private\AssetManagerEditorModule.cpp
 */

//UCLASS()
//class UMyAssetManager : public UAssetManager
class MyAssetManager
{
	//GENERATED_BODY()

public:
	//UMyAssetManager();
	//~UMyAssetManager();
	MyAssetManager();

	void init();
	void dispose();
};

MY_END_NAMESPACE