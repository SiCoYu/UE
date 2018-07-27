#include "MyProject.h"
#include "MPakFileSystem.h"
#include "MPakFileStream.h"
#include "MyMemoryInc.h"
#include "IPlatformFilePak.h"		// FPakFile
#include "UtilFileIO.h"
#include "MFileSystem.h"
#include "Ctx.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ue4  pak 加载
 * @url https://blog.csdn.net/sh15285118586/article/details/79648596
 * @url https://blog.csdn.net/u014532636/article/details/72844367
 * @url https://blog.csdn.net/u011047958/article/details/78539991
 * @url https://blog.csdn.net/liulong1567/article/details/71597892
 */
void MPakFileSystem::testLoadPak()
{
	//如果你想直接加载本地的pak的话,方法的参数列表删掉,然后把SaveArrayToFile这句话也删了,SaveContentDir填写你要加载的路径就可以了...
		//1.把下载好的文件保存起来
	//FString SaveContentDir = FPaths::GameContentDir() + TEXT("MultiOne.pak");
	FString SaveContentDir = UtilFileIO::GameContentDir(false) + TEXT("MultiOne.pak");
	//2.加载刚才保存的文件
	//获取当前使用的平台,这里使用的是WIN64平台
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	//初始化PakPlatformFile
	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();
	PakPlatformFile->Initialize(&PlatformFile, TEXT(""));
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);

	//获取Pak文件
	FPakFile PakFile(&PlatformFile, *SaveContentDir, false);
	//UE_LOG(LogClass, Log, TEXT("get PakFile..."))
	//设置pak文件的Mount点. 
	//FString MountPoint(FPaths::EngineContentDir()); //"/../../../Engine/Content/"对应路径
	FString MountPoint(UtilFileIO::EngineContentDir(false));
	PakFile.SetMountPoint(*MountPoint);
	//对pak文件mount到前面设定的MountPoint
	if (PakPlatformFile->Mount(*SaveContentDir, 0, *MountPoint))
	{
		//UE_LOG(LogClass, Log, TEXT("Mount Success"));
		TArray<FString> FileList;
		//得到Pak文件中MountPoint路径下的所有文件
		PakFile.FindFilesAtPath(FileList, *PakFile.GetMountPoint(), true, false, true);
		FStreamableManager StreamableManager;
		//对文件的路径进行处理,转换成StaticLoadObject的那种路径格式
		FString AssetName = FileList[0];
		FString AssetShortName = FPackageName::GetShortName(AssetName);
		FString LeftStr;
		FString RightStr;
		AssetShortName.Split(TEXT("."), &LeftStr, &RightStr);
		AssetName = TEXT("/Engine/") + LeftStr + TEXT(".") + LeftStr;    //我们加载的时候用的是这个路径
		FStringAssetReference reference = AssetName;
		//加载UObject
		UObject* LoadObject = StreamableManager.SynchronousLoad(reference);
		if (LoadObject != nullptr)
		{
			//UE_LOG(LogClass, Log, TEXT("Object Load Success..."));
			//TheLoadObject = LoadObject;
		}
		else
		{
			//UE_LOG(LogClass, Log, TEXT("Can not Load asset..."));
		}
	}
	else
	{
		UE_LOG(LogClass, Error, TEXT("Mount Failed"));
	}
}

MPakFileSystem::MPakFileSystem()
{
	//this->mPakPlatformFile = nullptr;
	//this->mBasePlatformFile = nullptr;
}

void MPakFileSystem::init()
{
	//IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	//this->mBasePlatformFile = &PlatformFile;
}

void MPakFileSystem::dispose()
{

}

MPakFileStream* MPakFileSystem::mountOnePak(FString& pakFileFullPath, FString& mountPoint)
{
	MPakFileStream* pakFileStream = nullptr;

	if (!this->mPath2PakFileStreamDic.containsKey(pakFileFullPath))
	{
		pakFileStream = MY_NEW MPakFileStream();
		this->mPath2PakFileStreamDic.add(pakFileFullPath, pakFileStream);

		pakFileStream->setPakFilePath(pakFileFullPath);
		pakFileStream->setMountPath(mountPoint);

		pakFileStream->init();
		pakFileStream->mount();
	}
	else
	{
		pakFileStream = this->mPath2PakFileStreamDic.value(pakFileFullPath);
	}

	return pakFileStream;
}

bool MPakFileSystem::mountPakFileSystem(FString& pakFileFullPath, FString& mountPoint)
{
	bool ret = false;

	//if (nullptr == this->mPakPlatformFile)
	//{
	//	this->mPakPlatformFile = new FPakPlatformFile();
	//	this->mPakPlatformFile->Initialize(this->mBasePlatformFile, TEXT(""));
	//}

	// Case 只能转换继承自 UObject 对象之间的转化
	// Engine\Source\Runtime\CoreUObject\Public\Templates\Casts.h
	//template <typename To, typename From>
	//FORCEINLINE To* Cast(From* Src)
	//{
	//	return TCastImpl<From, To>::DoCast(Src);
	//}
	//FPakPlatformFile* pakPlatformFile = Cast<FPakPlatformFile>(GFileSys->FindPlatformFile(*MFileSystem::PakFile));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FPakPlatformFile* pakPlatformFile = (FPakPlatformFile*)(GFileSys->FindPlatformFile(*MFileSystem::PakFile));

	if (nullptr == pakPlatformFile)
	{
		pakPlatformFile = new FPakPlatformFile();
		pakPlatformFile->Initialize(&PlatformFile, TEXT(""));

		GFileSys->SetPlatformFile(*pakPlatformFile);
	}
	else if(&PlatformFile != pakPlatformFile)
	{
		GFileSys->SetPlatformFile(*pakPlatformFile);
	}

	if (pakPlatformFile->Mount(*pakFileFullPath, 0, *mountPoint))
	{
		ret = true;
	}

	return ret;
}

bool MPakFileSystem::mountBaseFileSystem()
{
	//FPlatformFileManager::Get().SetPlatformFile(*(this->mBasePlatformFile));
	IPlatformFile& physicalPlatformFile = IPlatformFile::GetPlatformPhysical();
	GFileSys->SetPlatformFile(physicalPlatformFile);
	return true;
}

//FPakFile* MPakFileSystem::getPakFileByPath(FString& InPakFilename)
//{
//	FPakPlatformFile* pakPlatformFile = (FPakPlatformFile*)(GFileSys->FindPlatformFile(*MFileSystem::PakFile));
//
//	for (int PakIndex = 0; PakIndex < pakPlatformFile->PakFiles.Num(); PakIndex++)
//	{
//		if (pakPlatformFile->PakFiles[PakIndex].PakFile->GetFilename() == InPakFilename)
//		{
//			return pakPlatformFile->PakFiles[PakIndex].PakFile;
//		}
//	}
//
//	return nullptr;
//}

const FPakEntry* MPakFileSystem::getFileInPakByPath(FString& path)
{
	FPakPlatformFile* PlatformFile = (FPakPlatformFile*)(GFileSys->FindPlatformFile(*MFileSystem::PakFile));

	FPakFile* pakFile = nullptr;
	// UE 4.20 error C2440: 'initializing': cannot convert from 'bool' to 'const FPakEntry *'
	//const FPakEntry* pakEntry = PlatformFile->FindFileInPakFiles(*path, &pakFile, pakEntry);
	const FPakEntry* pakEntry = nullptr;
	bool ret = PlatformFile->FindFileInPakFiles(*path, &pakFile, pakEntry);

	return pakEntry;
}

bool MPakFileSystem::Unmount(const TCHAR* InPakFilename)
{
	FPakPlatformFile* PlatformFile = (FPakPlatformFile*)(GFileSys->FindPlatformFile(*MFileSystem::PakFile));
	PlatformFile->Unmount(InPakFilename);
	return true;
}

MY_END_NAMESPACE