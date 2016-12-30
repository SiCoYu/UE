#ifndef __MFileSys_H
#define __MFileSys_H

#include <string>

class LoadParam;
class FSandboxPlatformFile;

/**
 * @brief 本地文件系统
 Engine\Source\Runtime\Launch\Private\Android\AndroidJNI.cpp
 */
class MFileSys
{
public:
	static std::string msPersistentDataPath;		// 可写目录
	static std::string msStreamingAssetsPath;		// 只读目录

protected:
	// Engine\Source\Editor\UnrealEd\Private\Commandlets\CookCommandlet.cpp
	// Engine\Source\Editor\UnrealEd\Private\CookOnTheFlyServer.cpp
	FSandboxPlatformFile* mSandboxPlatformFile;

public:
	MFileSys();
	void init();
	void dispose();

	FSandboxPlatformFile* getSandboxPlatformFile();

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
};

#endif