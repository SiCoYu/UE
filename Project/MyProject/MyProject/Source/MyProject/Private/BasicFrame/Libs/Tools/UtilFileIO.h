#ifndef __UtilFileIO_H
#define __UtilFileIO_H

#include <string>
#include <sstream>
#include "Containers/UnrealString.h"
#include "IPlatformFileSandboxWrapper.h"	// FSandboxPlatformFile
#include "UtilStr.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilFileIO
{
public:
	// 结合路径到完整的目录，目前只支持两个，需要的继续添加
	template<class T0, class T1>
	static std::string Combine(T0 param0, T1 param1);

	// https://wiki.unrealengine.com/Packaged_Game_Paths,_Obtain_Directories_Based_on_Executable_Location
	static FString BaseDir();
	static FString RootDir();
	static FString GameDir();
	static FString GameContentDir();

	static FString GameSavedDir();
	static FString GameLogDir();

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
	static bool existFile(std::string& fullFilPath);
	static bool deleteFile(std::string& fullFilPath);
	// 获取扩展名
	static std::string UtilFileIO::getFileExt(std::string& path);
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