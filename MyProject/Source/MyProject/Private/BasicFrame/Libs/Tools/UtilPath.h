#ifndef __UtilPath_H_
#define __UtilPath_H_

#include <string>
#include <sstream>
#include "Containers/UnrealString.h"
#include "IPlatformFileSandboxWrapper.h"	// FSandboxPlatformFile

class UtilPath
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
};

// 模板实现
#include "UtilPath.inl"

//template<class T0, class T1>
//static std::string UtilPath::Combine(T0 param0, T1 param1)
//{
//	std::stringstream strStream;
//	strStream << param0 << "/" << "param1";
//
//	return strStream.str();
//}

#endif