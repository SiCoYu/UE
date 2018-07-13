#include "MyProject.h"
#include "MPakFileSystem.h"
#include "MPakFileStream.h"
#include "MyMemoryInc.h"
#include "IPlatformFilePak.h"		// FPakFile

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ue4  pak ����
 * @url https://blog.csdn.net/sh15285118586/article/details/79648596
 * @url https://blog.csdn.net/u014532636/article/details/72844367
 * @url https://blog.csdn.net/u011047958/article/details/78539991
 * @url https://blog.csdn.net/liulong1567/article/details/71597892
 */
//void MPakFileSystem::LoadPakComplete()
//{
//	//�������ֱ�Ӽ��ر��ص�pak�Ļ�,�����Ĳ����б�ɾ��,Ȼ���SaveArrayToFile��仰Ҳɾ��,SaveContentDir��д��Ҫ���ص�·���Ϳ�����...
//		//1.�����غõ��ļ���������
//	FString SaveContentDir = FPaths::GameContentDir() + TEXT("OutPak.pak");
//	//2.���ظղű�����ļ�
//	//��ȡ��ǰʹ�õ�ƽ̨,����ʹ�õ���WIN64ƽ̨
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//	//��ʼ��PakPlatformFile
//	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();
//	PakPlatformFile->Initialize(&PlatformFile, TEXT(""));
//	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
//
//	//��ȡPak�ļ�
//	FPakFile PakFile(*SaveContentDir, false);
//	UE_LOG(LogClass, Log, TEXT("get PakFile..."))
//	//����pak�ļ���Mount��. 
//	FString MountPoint(FPaths::EngineContentDir()); //"/../../../Engine/Content/"��Ӧ·��
//	PakFile.SetMountPoint(*MountPoint);
//	//��pak�ļ�mount��ǰ���趨��MountPoint
//	if (PakPlatformFile->Mount(*SaveContentDir, 0, *MountPoint))
//	{
//		UE_LOG(LogClass, Log, TEXT("Mount Success"));
//		TArray<FString> FileList;
//		//�õ�Pak�ļ���MountPoint·���µ������ļ�
//		PakFile.FindFilesAtPath(FileList, *PakFile.GetMountPoint(), true, false, true);
//		FStreamableManager StreamableManager;
//		//���ļ���·�����д���,ת����StaticLoadObject������·����ʽ
//		FString AssetName = FileList[0];
//		FString AssetShortName = FPackageName::GetShortName(AssetName);
//		FString LeftStr;
//		FString RightStr;
//		AssetShortName.Split(TEXT("."), &LeftStr, &RightStr);
//		AssetName = TEXT("/Engine/") + LeftStr + TEXT(".") + LeftStr;    //���Ǽ��ص�ʱ���õ������·��
//		FStringAssetReference reference = AssetName;
//		//����UObject
//		UObject* LoadObject = StreamableManager.SynchronousLoad(reference);
//		if (LoadObject != nullptr)
//		{
//			UE_LOG(LogClass, Log, TEXT("Object Load Success..."))
//				TheLoadObject = LoadObject;
//		}
//		else
//		{
//			UE_LOG(LogClass, Log, TEXT("Can not Load asset..."))
//		}
//	}
//	else
//	{
//		UE_LOG(LogClass, Error, TEXT("Mount Failed"));
//	}
//}

MPakFileSystem::MPakFileSystem()
{

}

void MPakFileSystem::init()
{

}

void MPakFileSystem::dispose()
{

}

void MPakFileSystem::mountOnePak(FString& pakFileFullPath, FString& mountPoint)
{
	if (!this->mPath2PakFileStreamDic.containsKey(pakFileFullPath))
	{
		MPakFileStream* pakFileStream = MY_NEW MPakFileStream();
		this->mPath2PakFileStreamDic.add(pakFileFullPath, pakFileStream);

		pakFileStream->setPakFilePath(pakFileFullPath);
		pakFileStream->setPakFilePath(mountPoint);

		pakFileStream->init();
		pakFileStream->mount();
	}
}

MY_END_NAMESPACE