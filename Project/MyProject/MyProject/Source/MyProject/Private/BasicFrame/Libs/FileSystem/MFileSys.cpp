#include "MyProject.h"
#include "MFileSys.h"
#include "Containers/UnrealString.h"		// FString
#include "HAL/PlatformFilemanager.h"		// FPlatformFileManager
#include "IPlatformFileSandboxWrapper.h"	// FSandboxPlatformFile
#include "UtilStr.h"
#include "UtilFileIO.h"

MY_BEGIN_NAMESPACE(MyNS)

std::string MFileSys::msPersistentDataPath = "";
std::string MFileSys::msStreamingAssetsPath = "";
std::string MFileSys::msDataStreamStreamingAssetsPath = "";

MFileSys::MFileSys()
{
	// 初始化 SandBox 文件系统
	this->mSandboxPlatformFile = new FSandboxPlatformFile(false);
}

void MFileSys::init()
{
	FString contentPath = UtilFileIO::GameContentDir();
	std::string path = UtilStr::ConvFString2StdStr(contentPath);
	std::string searchPath = "";

	searchPath = path + "MyAsset/Lua/";
	this->mLuaSearchPathList.add(searchPath);

	searchPath = path + "MyAsset/Lua/Socket/";
	this->mLuaSearchPathList.add(searchPath);

	searchPath = path + "MyAsset/Lua/ZeroBraneStudio/";
	this->mLuaSearchPathList.add(searchPath);

	// 初始化 SandBox 文件系统
	//this->mSandboxPlatformFile = new FSandboxPlatformFile(false);
	//FString OutputDirectory = GetOutputDirectoryOverride();
	// UE 4.19.2 warning C4996: 'FPaths::GameDir': FPaths::GameDir() has been superseded by FPaths::ProjectDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//FString OutputDirectory = FPaths::GameDir();
	FString OutputDirectory = FPaths::ProjectDir();
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
	CacheFolderPath = UtilFileIO::GameSavedDir() / TEXT("ProgramBinaryCache");
#endif

	MFileSys::msPersistentDataPath = UtilStr::ConvFString2StdStr(CacheFolderPath);

	CacheFolderPath = UtilFileIO::GameContentDir();
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

std::string MFileSys::getLuaPath(std::string luaPackage)
{
	std::string old_value = ".";
	std::string new_value = "/";

	std::string replace = UtilStr::replaceAllDistinct(luaPackage, old_value, new_value);
	std::string fullPath;

	for (auto searchPath : this->mLuaSearchPathList.getList())
	{
		fullPath = searchPath + replace + ".lua";

		if (UtilFileIO::FileExists(fullPath))
		{
			break;
		}
		else
		{
			fullPath = "";
		}
	}

	return fullPath;
}

void MFileSys::addSearchPath(std::string path)
{

}

MY_END_NAMESPACE