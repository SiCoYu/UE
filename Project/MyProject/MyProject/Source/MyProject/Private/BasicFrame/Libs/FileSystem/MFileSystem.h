#ifndef __MFileSys_H
#define __MFileSys_H

#include <string>
#include "Containers/UnrealString.h"	// FString
#include "MList.h"
#include "GObject.h"
#include "PlatformDefine.h"

class FSandboxPlatformFile;
class IPlatformFile;

MY_BEGIN_NAMESPACE(MyNS)

class LoadParam;

/**
 * @brief 本地文件系统
 * @url Engine\Source\Runtime\Launch\Private\Android\AndroidJNI.cpp
 * IFileManager 就是对当前的文件系统进行操作， 会调用 FPlatformFileManager 的 GetPlatformFile 获取当前文件系统，而 FPlatformFileManager 是管理当前所有文件系统的，当前可能有物理文件系统， Pak 文件系统，一个是管理器，一个是操作当前文件系统的接口
 */
class MFileSystem : public GObject
{
public:
	static std::string msPersistentDataPath;		// 可写目录
	static std::string msStreamingAssetsPath;		// 只读目录
	static std::string msDataStreamStreamingAssetsPath;
	static std::string msDataStreamPersistentDataPath; 
	static std::string msDataStreamResourcesPath;

	static FString msProjectContentPathPrefix;
	static FString msEngineContentPathPrefix;

	// Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
	// IPlatformFile* PlatformFile = ConditionallyCreateFileWrapper(TEXT("PakFile"), CurrentPlatformFile, CmdLine);
	static FString PakFile;
	static FString CachedReadFile;
	static FString SandboxFile;
	static FString StreamingFile;
	static FString NetworkFile;
	static FString ProfileFile;
	static FString FileOpenLog;
	static FString LogFile;

protected:
	// 编辑器 Sandbox 文件系统
	// Engine\Source\Editor\UnrealEd\Private\Commandlets\CookCommandlet.cpp
	// Engine\Source\Editor\UnrealEd\Private\CookOnTheFlyServer.cpp
	FSandboxPlatformFile* mSandboxPlatformFile;
	MList<std::string> mLuaSearchPathList;

public:
	MFileSystem();

public:
	void init();
	void dispose();

	FSandboxPlatformFile* getSandboxPlatformFile();
	std::string getLuaPath(std::string luaPackage);

protected:
	static void initFileSys();

public:
	// 获取本地可以读取的目录，但是不能写
	static std::string getLocalReadDir();
	// 获取本地可以写的目录
	static std::string getLocalWriteDir();
	// 获取真正的加载参数
	static void modifyLoadParam(std::string resPath, LoadParam* param);

public:
	// Engine\Source\Runtime\Core\Private\Android\AndroidFile.cpp
	// FString GFilePathBase;	getExternalStorageDirectory
	// FString GExternalFilePath;	getExternalFilesDir
	//const FString &GetFileBasePath()

	// https://answers.unrealengine.com/questions/476998/ue4game-folder-on-external-storage-android.html
	// I found a global variable GFilePathBase at line 865 in file \Engine\Source\Runtime\Launch\Private\Android\AndroidJNI.cpp.It is assigned to ExternalStorageDirectory(/ storage / sdcard0) of Android.And another global variable GExternalFilePath at line 926 is assigned to ExternalFilesDir(/ storage / sdcard0 / Android / data / package / files),

	// 是时候弄清楚getExternalStorageDirectory()和getExternalFilesDir()的区别了 
	// http://blog.csdn.net/nugongahou110/article/details/48154859

	// Engine\Source\Runtime\Launch\Private\Android\AndroidJNI.cpp
	// GFilePathBase = FString(nativePathString);

	void addSearchPath(std::string path);
	IPlatformFile* GetPlatformFile();
	void SetPlatformFile(IPlatformFile& NewTopmostPlatformFile);
	IPlatformFile* FindPlatformFile(const TCHAR* Name);
	IPlatformFile* GetPlatformFile(const TCHAR* Name);
};

MY_END_NAMESPACE

#endif