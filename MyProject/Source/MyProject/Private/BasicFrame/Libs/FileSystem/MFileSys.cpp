#include "MyProject.h"
#include "MFileSys.h"
#include "Containers/UnrealString.h"		// FString
#include "HAL/PlatformFilemanager.h"		// FPlatformFileManager
#include "IPlatformFileSandboxWrapper.h"	// FSandboxPlatformFile
#include "UtilStr.h"
#include "UtilPath.h"

std::string MFileSys::msPersistentDataPath = "";
std::string MFileSys::msStreamingAssetsPath = "";

MFileSys::MFileSys()
{
	// 初始化 SandBox 文件系统
	this->mSandboxPlatformFile = new FSandboxPlatformFile(false);
}

void MFileSys::init()
{
	// 初始化 SandBox 文件系统
	//mSandboxPlatformFile = new FSandboxPlatformFile(false);
	//FString OutputDirectory = GetOutputDirectoryOverride();
	FString OutputDirectory = FPaths::GameDir();
	this->mSandboxPlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), *FString::Printf(TEXT("-sandbox=\"%s\""), *OutputDirectory));

	MFileSys::initFileSys();
}

void MFileSys::dispose()
{
	delete this->mSandboxPlatformFile;
}

FSandboxPlatformFile* MFileSys::getSandboxPlatformFile()
{
	return this->mSandboxPlatformFile;
}

void MFileSys::initFileSys()
{
	// Engine\Source\Runtime\OpenGLDrv\Private\OpenGLShaders.cpp
	FString CacheFolderPath;
#if PLATFORM_ANDROID
	extern FString GExternalFilePath;
	CacheFolderPath = GExternalFilePath / TEXT("ProgramBinaryCache");
#else
	CacheFolderPath = UtilPath::GameSavedDir() / TEXT("ProgramBinaryCache");
#endif

	MFileSys::msPersistentDataPath = UtilStr::ConvFString2StdStr(CacheFolderPath);

	CacheFolderPath = UtilPath::GameContentDir();
	MFileSys::msStreamingAssetsPath = UtilStr::ConvFString2StdStr(CacheFolderPath);
}

// 获取本地可以读取的目录，但是不能写
std::string MFileSys::getLocalReadDir()
{
	return MFileSys::msStreamingAssetsPath;
}

// 获取本地可以写的目录
std::string MFileSys::getLocalWriteDir()
{
	return MFileSys::msPersistentDataPath;
}

void MFileSys::modifyLoadParam(std::string resPath, LoadParam* param)
{

}