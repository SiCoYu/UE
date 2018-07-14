#pragma once

#include "Containers/UnrealString.h"	// FString
#include "GObject.h"
#include "MDictionary.h"
#include "PlatformDefine.h"

class FPakPlatformFile;
class IPlatformFile;

MY_BEGIN_NAMESPACE(MyNS)

class MPakFileStream;

/**
 * @brief ue4  pak 加载
 * @brief https://blog.csdn.net/u014532636/article/details/72844367
 */
class MPakFileSystem : public GObject
{
protected:
	//FPakPlatformFile* mPakPlatformFile;
	//IPlatformFile* mBasePlatformFile;	// 原始基础平台文件
	MDictionary<FString, MPakFileStream*> mPath2PakFileStreamDic;

public:
	MPakFileSystem();

	void init();
	void dispose();

	void testLoadPak();

	MPakFileStream* getPakFileStream(FString& pakFileFullPath);
	MPakFileStream* mountOnePak(FString& pakFileFullPath, FString& mountPoint);

	bool mountPakFileSystem(FString& pakFileFullPath, FString& mountPoint);
	bool mountBaseFileSystem();
};

MY_END_NAMESPACE