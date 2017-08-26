#include "MyProject.h"
#include "MyMountPak.h"

UMyMountPak::UMyMountPak(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMyMountPak::LoadPakComplete()
{       //�������ֱ�Ӽ��ر��ص�pak�Ļ�,�����Ĳ����б�ɾ��,Ȼ���SaveArrayToFile��仰Ҳɾ��,SaveContentDir��д��Ҫ���ص�·���Ϳ�����...  
        //1.�����غõ��ļ���������  
    FString SaveContentDir = FPaths::GameContentDir() + TEXT("OutPak.pak");  
    //2.���ظղű�����ļ�  
    //��ȡ��ǰʹ�õ�ƽ̨,����ʹ�õ���WIN64ƽ̨  
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();  
    //��ʼ��PakPlatformFile  
    FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();  
    PakPlatformFile->Initialize(&PlatformFile, TEXT(""));  
    FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);  
      
    //��ȡPak�ļ�  
    FPakFile PakFile(*SaveContentDir, false);  
    UE_LOG(LogClass, Log, TEXT("get PakFile..."))  
    //����pak�ļ���Mount��.   
    FString MountPoint(FPaths::EngineContentDir()); //"/../../../Engine/Content/"��Ӧ·��  
    PakFile.SetMountPoint(*MountPoint);  
    //��pak�ļ�mount��ǰ���趨��MountPoint  
    if (PakPlatformFile->Mount(*SaveContentDir, 0, *MountPoint))  
    {  
        UE_LOG(LogClass, Log, TEXT("Mount Success"));  
        TArray<FString> FileList;  
        //�õ�Pak�ļ���MountPoint·���µ������ļ�  
        PakFile.FindFilesAtPath(FileList, *PakFile.GetMountPoint(), true, false, true);  
        FStreamableManager StreamableManager;  
        //���ļ���·�����д���,ת����StaticLoadObject������·����ʽ  
        FString AssetName = FileList[0];  
        FString AssetShortName = FPackageName::GetShortName(AssetName);  
        FString LeftStr;  
        FString RightStr;  
        AssetShortName.Split(TEXT("."), &LeftStr, &RightStr);  
        AssetName = TEXT("/Engine/") + LeftStr + TEXT(".") + LeftStr;    //���Ǽ��ص�ʱ���õ������·��  
        FStringAssetReference reference = AssetName;  
        //����UObject  
        UObject* LoadObject = StreamableManager.SynchronousLoad(reference);  
        if (LoadObject != nullptr)  
        {  
            UE_LOG(LogClass, Log, TEXT("Object Load Success..."))  
                TheLoadObject = LoadObject;  
        }  
        else  
        {  
            UE_LOG(LogClass, Log, TEXT("Can not Load asset..."))  
        }  
    }  
    else  
    {  
        UE_LOG(LogClass, Error, TEXT("Mount Failed"));  
    }  
}  