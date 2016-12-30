#ifndef __MFileSys_H
#define __MFileSys_H

#include <string>

class LoadParam;
class FSandboxPlatformFile;

/**
 * @brief 本地文件系统
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
};

#endif