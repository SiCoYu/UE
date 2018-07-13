#include "MyProject.h"
#include "MPakFileSystem.h"
#include "MPakFileStream.h"
#include "MyMemoryInc.h"
#include "IPlatformFilePak.h"		// FPakFile

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ue4  pak 加载
 * @url https://blog.csdn.net/sh15285118586/article/details/79648596
 * @url https://blog.csdn.net/u014532636/article/details/72844367
 * @url https://blog.csdn.net/u011047958/article/details/78539991
 * @url https://blog.csdn.net/liulong1567/article/details/71597892
 */
//void MPakFileSystem::LoadPakComplete()
//{
//	//如果你想直接加载本地的pak的话,方法的参数列表删掉,然后把SaveArrayToFile这句话也删了,SaveContentDir填写你要加载的路径就可以了...
//		//1.把下载好的文件保存起来
//	FString SaveContentDir = FPaths::GameContentDir() + TEXT("OutPak.pak");
//	//2.加载刚才保存的文件
//	//获取当前使用的平台,这里使用的是WIN64平台
//	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//	//初始化PakPlatformFile
//	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();
//	PakPlatformFile->Initialize(&PlatformFile, TEXT(""));
//	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
//
//	//获取Pak文件
//	FPakFile PakFile(*SaveContentDir, false);
//	UE_LOG(LogClass, Log, TEXT("get PakFile..."))
//	//设置pak文件的Mount点. 
//	FString MountPoint(FPaths::EngineContentDir()); //"/../../../Engine/Content/"对应路径
//	PakFile.SetMountPoint(*MountPoint);
//	//对pak文件mount到前面设定的MountPoint
//	if (PakPlatformFile->Mount(*SaveContentDir, 0, *MountPoint))
//	{
//		UE_LOG(LogClass, Log, TEXT("Mount Success"));
//		TArray<FString> FileList;
//		//得到Pak文件中MountPoint路径下的所有文件
//		PakFile.FindFilesAtPath(FileList, *PakFile.GetMountPoint(), true, false, true);
//		FStreamableManager StreamableManager;
//		//对文件的路径进行处理,转换成StaticLoadObject的那种路径格式
//		FString AssetName = FileList[0];
//		FString AssetShortName = FPackageName::GetShortName(AssetName);
//		FString LeftStr;
//		FString RightStr;
//		AssetShortName.Split(TEXT("."), &LeftStr, &RightStr);
//		AssetName = TEXT("/Engine/") + LeftStr + TEXT(".") + LeftStr;    //我们加载的时候用的是这个路径
//		FStringAssetReference reference = AssetName;
//		//加载UObject
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