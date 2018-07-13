#pragma once

#include "Containers/UnrealString.h"	// FString
#include "GObject.h"
#include "MDictionary.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MPakFileStream;

/**
 * @brief ue4  pak ����
 * @brief https://blog.csdn.net/u014532636/article/details/72844367
 */
class MPakFileSystem : public GObject
{
protected:
	MDictionary<FString, MPakFileStream*> mPath2PakFileStreamDic;

public:
	MPakFileSystem();

	void init();
	void dispose();

	MPakFileStream* getPakFileStream(FString& pakFileFullPath);
	MPakFileStream* mountOnePak(FString& pakFileFullPath, FString& mountPoint);
};

MY_END_NAMESPACE