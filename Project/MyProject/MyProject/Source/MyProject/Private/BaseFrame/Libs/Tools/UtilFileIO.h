#ifndef __UtilFileIO_H
#define __UtilFileIO_H

#include <string>
#include <sstream>
#include "Containers/UnrealString.h"		// FString
#include "IPlatformFileSandboxWrapper.h"	// FSandboxPlatformFile
#include "UtilStr.h"
#include "PlatformDefine.h"
#include "GenericPlatform/GenericPlatformFile.h"	// FDirectoryVisitor
#include "MyFileDelegate.h"		// MyTraverseDirectoryDelegate

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @ref https://wiki.unrealengine.com/File_Management,_Create_Folders,_Delete_Files,_and_More
 */
// error LNK2019: unresolved external symbol "public: static class FString __cdecl MyNS::UtilFileIO::ProjectContentDir(bool)" (?ProjectContentDir@UtilFileIO@MyNS@@SA?AVFString@@_N@Z) referenced in function "public: void __cdecl FExportAssetDependeciesModule::onExportAllPluginButtonClicked(void)" (?onExportAllPluginButtonClicked@FExportAssetDependeciesModule@@QEAAXXZ)
class MYPROJECT_API UtilFileIO
{
public:
	// 结合路径到完整的目录，目前只支持两个，需要的继续添加
	template<class T0, class T1>
	static std::string Combine(T0 param0, T1 param1);
	static FString Combine(FString& param0, FString& param1);

	// https://answers.unrealengine.com/questions/498328/androidconvertrelativepathtofull-didnt-work.html
	// From speaking to one of our Android developers, this is intended and BaseDir() should be returning nothing when on mobile devices, seeing as the folders from your PC do not exist on the device and it wouldn't make much sense to replace the relative path with the full original path. 
	// https://wiki.unrealengine.com/Packaged_Game_Paths,_Obtain_Directories_Based_on_Executable_Location
	static FString BaseDir();
	static FString RootDir(bool isAbsPath = true);
	static FString ProjectDir(bool isAbsPath = true);
	static FString ProjectContentDir(bool isAbsPath = true);
	static FString ProjectPluginsDir();

	static FString EngineContentDir(bool isAbsPath = true);
	static FString ProjectSavedDir(bool isAbsPath = true);
	static FString ProjectLogDir(bool isAbsPath = true);
	static FString ProjectPersistentDownloadDir();

	static FString GetFilenameOnDisk(FString FullFilename);
	static FString ConvertToSandboxPath(FString FullFilename);

	static FString FPaths_ConvertToSandboxPath(FString FullFilename);
	static void NormalizeDirectoryName(FString& InPath);

	static bool FileExists(const std::string& InPath);

	static std::string combine(
		std::string& path0, 
		std::string& path1, 
		std::string& path2 = UtilStr::msDefaultStr,
		std::string& path3 = UtilStr::msDefaultStr
	);
	static bool existFile(std::string& fullFilePath);
	static bool ExistFile(FString& fullFilePath);
	static bool deleteFile(std::string& fullFilePath);
	static bool DeleteFile(FString& absoluteFilePath);
	static bool IsFile(FString& absoluteFilePath);
	static bool IsDirectory(FString& absoluteFilePath);
	static void Normalize(FString& path);

	// 获取扩展名
	static std::string getFileExt(std::string& path);
	// 获取文件名字，没有路径，但是有扩展名字
	static std::string getFileNameWithExt(std::string& fullPath);
	// 获取文件名字，没有扩展名字
	static std::string getFileNameNoExt(std::string& fullPath);
	// 获取文件路径，没有文件名字
	static std::string getFilePathNoName(std::string& fullPath);
	static std::string getFileDir(std::string& fullPath);
	// 获取文件路径，没有文件名字扩展
	static std::string getFilePathNoExt(std::string& fullPath);
	// 获取当前文件的父目录名字
	static std::string getFileParentDirName(std::string& fullPath);

	// 转换 StreamingAssets 到 Mount 目录
	static FString convStreamingAssetsPathToMountPath(FString& streamingAssetsPath);
	static bool isBluePrints(FString& filePath);

	// Directory
	static bool DirectoryExists(const FString& absoluteFilePath);
	static bool existDirectory(std::string& absoluteFilePath);
	static bool CheckOrCreateDirectory(const FString& absoluteFilePath);
	static int64 FileSize(const FString& absoluteFilePath);
	static bool MoveFile(const FString& absoluteSourcePath, const FString& absoluteDestinationPath);
	static bool RenameFile(const FString& absoluteSourcePath, const FString& absoluteDestinationPath);

	static bool CreateDirectory(const FString& absoluteFilePath, bool isRecurse = false);
	static bool createDirectory(std::string& absoluteFilePath, bool isRecurse = false);
	static void traverseDirectory(
		FString& absoluteSourcePath,
		FString& absoluteDestinationPath, 
		MyTraverseDirectoryDelegate dirHandle, 
		MyTraverseDirectoryDelegate fileHandle,
		bool isRecurse = false,
		bool isCreateDestPath = false
	);
	static bool GetAllFile(FString& absoluteSourcePath, TArray<FString>& FilenamesOut, bool Recursive = false, const FString& FilterByExtension = "");
	static bool GetAllDirectory(FString& absoluteSourcePath, TArray<FString>& DirsOut, bool Recursive = false, const FString& ContainsStr = "");
	static bool LoadFileToString(FString& absolutePath, FString& resultStr);

	// https://answers.unrealengine.com/questions/498328/androidconvertrelativepathtofull-didnt-work.html
	static FString GetAndroidFileBasePath();
	// https://answers.unrealengine.com/questions/498328/androidconvertrelativepathtofull-didnt-work.html
	// You shouldn't try to read or write to GetFileBasePath() directly since anything here is possibly inside another file wrapper. You should read and write native files to GExternalFilePath instead. If you really need to get this, though, you can do it like so:
	static FString ConvertRelativePathToFull(FString& relativePath);
	static FString GetFileBasePath();
	static bool TryConvertLongPackageNameToFilename(const FString& InLongPackageName, FString& OutFilename, const FString& InExtension = TEXT(""));
	static bool TryConvertFilenameToLongPackageName(const FString& InFilename, FString& OutPackageName, FString* OutFailureReason = nullptr);
	static void RegisterMountPoint(const FString& RootPath, const FString& ContentPath);
	static void UnRegisterMountPoint(const FString& RootPath, const FString& ContentPath);
};

MY_END_NAMESPACE

// 模板实现
#include "UtilFileIO.inl"

//template<class T0, class T1>
//static std::string UtilFileIO::Combine(T0 param0, T1 param1)
//{
//	std::stringstream strStream;
//	strStream << param0 << "/" << "param1";
//
//	return strStream.str();
//}

#endif